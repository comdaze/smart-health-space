#!/usr/bin/env python3.9

# Copyright 2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License").
# You may not use this file except in compliance with the License.
# A copy of the License is located at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# or in the "license" file accompanying this file. This file is distributed
# on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
# express or implied. See the License for the specific language governing
# permissions and limitations under the License.

#
# clean-up.py
#
# cleans up after workshop
"""Clean up workshop resources"""


import os
import time
import argparse
import boto3
from botocore.config import Config

parser = argparse.ArgumentParser()
parser.add_argument("-e", "--endpoint", action="store", required=True, dest="host", help="Your AWS IoT custom endpoint")
parser.add_argument("-id", "--clientId", action="store", dest="clientId", default="basicPubSub",
                    help="Targeted client id")
parser.add_argument("-r", "--region", action="store", required=True, dest="region", default="ap-northeast-1",
                    help="AWS Region")

args = parser.parse_args()
IOT_ENDPOINT = args.host
REGION = args.region
my_config = Config(
    region_name = REGION,
    signature_version = 'v4',
    retries = {
        'max_attempts': 10,
        'mode': 'standard'
    }
)
c_iot = boto3.client('iot', config=my_config)
c_iot_data = boto3.client('iot-data', endpoint_url='https://{}'.format(IOT_ENDPOINT), config=my_config)

c_iot.update_indexing_configuration(
    thingIndexingConfiguration={
        'thingIndexingMode': 'REGISTRY_AND_SHADOW',
    },
    thingGroupIndexingConfiguration={
        'thingGroupIndexingMode': 'ON',
    }
)

#IOT_ENDPOINT = os.environ['IOT_ENDPOINT']
#IOT_ENDPOINT= 'a2u3inau7j0faa-ats.iot.ap-northeast-1.amazonaws.com'
#######################################################################
QUERY_STRINGS = [
    'EduKit_Policy', 'microchip-tng'
]
THING_NAMES = [args.clientId,]
THING_GROUPS = []
POLICY_NAMES = [
    'EduKit_Policy'
]
#######################################################################

def delete_thing(thing_name):
    """deletes a thing in AWS IoT Core"""
    global POLICY_NAMES

    print("  DELETING thing_name: {}".format(thing_name))

    try:
        r_principals = c_iot.list_thing_principals(thingName=thing_name)
    except Exception as list_thing_principals_error:
        print("ERROR listing thing principals: {}".format(list_thing_principals_error))
        r_principals = {'principals': []}

    for arn in r_principals['principals']:
        cert_id = arn.split('/')[1]
        print("  arn: {} cert_id: {}".format(arn, cert_id))

        r_detach_thing = c_iot.detach_thing_principal(thingName=thing_name,principal=arn)
        print("  DETACH THING: {}".format(r_detach_thing))

        r_upd_cert = c_iot.update_certificate(certificateId=cert_id,newStatus='INACTIVE')
        print("  INACTIVE: {}".format(r_upd_cert))

        r_policies = c_iot.list_principal_policies(principal=arn)
        #print("    r_policies: {}".format(r_policies))

        for pol in r_policies['policies']:
            pol_name = pol['policyName']
            print("    pol_name: {}".format(pol_name))
            POLICY_NAMES.append(pol_name)
            r_detach_pol = c_iot.detach_policy(policyName=pol_name,target=arn)
            print("    DETACH POL: {}".format(r_detach_pol))

        r_del_cert = c_iot.delete_certificate(certificateId=cert_id,forceDelete=True)
        print("  DEL CERT: {}".format(r_del_cert))

    r_del_thing = c_iot.delete_thing(thingName=thing_name)
    print("  DELETE THING: {}\n".format(r_del_thing))



for query_string in QUERY_STRINGS:
    print("query_string: {}".format(query_string))

    response = c_iot.search_index(
        queryString=query_string,
    )

    print("response:\n{}".format(response))
    for thing in response["things"]:
        THING_NAMES.append(thing["thingName"])

    while 'nextToken' in response:
        next_token = response['nextToken']
        print("next token: {}".format(next_token))
        response = c_iot.search_index(
            queryString=query_string,
            nextToken=next_token
        )
        print("response:\n{}".format(response))
        for thing in response["things"]:
            THING_NAMES.append(thing["thingName"])

#print("END WHILE")
print("--------------------------------------\n")
print("thing names to be DELETED:\n{}\n".format(THING_NAMES))
print("number of things to be deleted: {}\n".format(len(THING_NAMES)))
print("--------------------------------------\n")

input("THE DEVICES IN THE LIST ABOVE WILL BE DELETED INCLUDING CERTIFICATES AND POLICIES\n== \
press <enter> to continue, <ctrl+c> to abort!\n")
#sys.exit()

for THING_NAME in THING_NAMES:
    print("THING NAME: {}".format(THING_NAME))
    delete_thing(THING_NAME)
    time.sleep(0.5) # avoid to run into api throttling

for thing_group in THING_GROUPS:
    print(thing_group)
    r_del_grp = c_iot.delete_thing_group(thingGroupName=thing_group)
    print("DELETE THING GROUP: {}".format(r_del_grp))


for policy_name in POLICY_NAMES:
    print("DELETE policy: {}".format(policy_name))
    try:
        r_targets = c_iot.list_targets_for_policy(
            policyName=policy_name,
            pageSize=10
        )
        for arn in r_targets['targets']:
            print("DETACH: {}".format(arn))
            r_detach_pol = c_iot.detach_policy(policyName=policy_name,target=arn)
            print("r_detach_pol: {}\n".format(r_detach_pol))

        while 'nextMarker' in r_targets:
            r_targets = c_iot.list_targets_for_policy(
                policyName=policy_name,
                marker=r_targets['nextMarker'],
                pageSize=2
            )
            for arn in r_targets['targets']:
                print("DETACH: {}".format(arn))
                r_detach_pol = c_iot.detach_policy(policyName=policy_name,target=arn)
                print("r_detach_pol: {}\n".format(r_detach_pol))


        r_targets = c_iot.list_targets_for_policy(policyName=policy_name, pageSize=250)
        for arn in r_targets['targets']:
            print("DETACH: {}".format(arn))
            r_detach_pol = c_iot.detach_policy(policyName=policy_name,target=arn)
            print("r_detach_pol: {}\n".format(r_detach_pol))

        r_versions = c_iot.list_policy_versions(policyName=policy_name)
        print('policy_name: {} versions: {}'.format(
            policy_name, r_versions['policyVersions']))

        for version in r_versions["policyVersions"]:
            if not version['isDefaultVersion']:
                print(
                    'policy_name: {} deleting policy version: {}'.format(
                        policy_name, version['versionId']
                    )
                )
                c_iot.delete_policy_version(policyName=policy_name,
                    policyVersionId=version['versionId'])

        if policy_name == os.environ['IOT_POLICY']:
            continue
        r_del_pol = c_iot.delete_policy(policyName=policy_name)
        print("r_del_pol: {}".format(r_del_pol))
    except c_iot.exceptions.ResourceNotFoundException:
        print("policy_name \"{}\" does not exist".format(policy_name))
    except Exception as delete_policy_error:
        print("ERROR: {}".format(delete_policy_error))
