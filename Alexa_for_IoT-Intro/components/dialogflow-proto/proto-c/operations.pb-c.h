/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: google/longrunning/operations.proto */

#ifndef PROTOBUF_C_google_2flongrunning_2foperations_2eproto__INCLUDED
#define PROTOBUF_C_google_2flongrunning_2foperations_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "annotations.pb-c.h"
#include "any.pb-c.h"
#include "empty.pb-c.h"
#include "status.pb-c.h"

typedef struct _Google__Longrunning__Operation Google__Longrunning__Operation;
typedef struct _Google__Longrunning__GetOperationRequest Google__Longrunning__GetOperationRequest;
typedef struct _Google__Longrunning__ListOperationsRequest Google__Longrunning__ListOperationsRequest;
typedef struct _Google__Longrunning__ListOperationsResponse Google__Longrunning__ListOperationsResponse;
typedef struct _Google__Longrunning__CancelOperationRequest Google__Longrunning__CancelOperationRequest;
typedef struct _Google__Longrunning__DeleteOperationRequest Google__Longrunning__DeleteOperationRequest;


/* --- enums --- */


/* --- messages --- */

typedef enum {
  GOOGLE__LONGRUNNING__OPERATION__RESULT__NOT_SET = 0,
  GOOGLE__LONGRUNNING__OPERATION__RESULT_ERROR = 4,
  GOOGLE__LONGRUNNING__OPERATION__RESULT_RESPONSE = 5
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(GOOGLE__LONGRUNNING__OPERATION__RESULT)
} Google__Longrunning__Operation__ResultCase;

/*
 * This resource represents a long-running operation that is the result of a
 * network API call.
 */
struct  _Google__Longrunning__Operation
{
  ProtobufCMessage base;
  /*
   * The server-assigned name, which is only unique within the same service that
   * originally returns it. If you use the default HTTP mapping, the
   * `name` should have the format of `operations/some/unique/name`.
   */
  char *name;
  /*
   * Service-specific metadata associated with the operation.  It typically
   * contains progress information and common metadata such as create time.
   * Some services might not provide such metadata.  Any method that returns a
   * long-running operation should document the metadata type, if any.
   */
  Google__Protobuf__Any *metadata;
  /*
   * If the value is `false`, it means the operation is still in progress.
   * If true, the operation is completed, and either `error` or `response` is
   * available.
   */
  protobuf_c_boolean done;
  Google__Longrunning__Operation__ResultCase result_case;
  union {
    /*
     * The error result of the operation in case of failure or cancellation.
     */
    Google__Rpc__Status *error;
    /*
     * The normal response of the operation in case of success.  If the original
     * method returns no data on success, such as `Delete`, the response is
     * `google.protobuf.Empty`.  If the original method is standard
     * `Get`/`Create`/`Update`, the response should be the resource.  For other
     * methods, the response should have the type `XxxResponse`, where `Xxx`
     * is the original method name.  For example, if the original method name
     * is `TakeSnapshot()`, the inferred response type is
     * `TakeSnapshotResponse`.
     */
    Google__Protobuf__Any *response;
  };
};
#define GOOGLE__LONGRUNNING__OPERATION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__longrunning__operation__descriptor) \
    , (char *)protobuf_c_empty_string, NULL, 0, GOOGLE__LONGRUNNING__OPERATION__RESULT__NOT_SET, {0} }


/*
 * The request message for [Operations.GetOperation][google.longrunning.Operations.GetOperation].
 */
struct  _Google__Longrunning__GetOperationRequest
{
  ProtobufCMessage base;
  /*
   * The name of the operation resource.
   */
  char *name;
};
#define GOOGLE__LONGRUNNING__GET_OPERATION_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__longrunning__get_operation_request__descriptor) \
    , (char *)protobuf_c_empty_string }


/*
 * The request message for [Operations.ListOperations][google.longrunning.Operations.ListOperations].
 */
struct  _Google__Longrunning__ListOperationsRequest
{
  ProtobufCMessage base;
  /*
   * The name of the operation collection.
   */
  char *name;
  /*
   * The standard list filter.
   */
  char *filter;
  /*
   * The standard list page size.
   */
  int32_t page_size;
  /*
   * The standard list page token.
   */
  char *page_token;
};
#define GOOGLE__LONGRUNNING__LIST_OPERATIONS_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__longrunning__list_operations_request__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, 0, (char *)protobuf_c_empty_string }


/*
 * The response message for [Operations.ListOperations][google.longrunning.Operations.ListOperations].
 */
struct  _Google__Longrunning__ListOperationsResponse
{
  ProtobufCMessage base;
  /*
   * A list of operations that matches the specified filter in the request.
   */
  size_t n_operations;
  Google__Longrunning__Operation **operations;
  /*
   * The standard List next-page token.
   */
  char *next_page_token;
};
#define GOOGLE__LONGRUNNING__LIST_OPERATIONS_RESPONSE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__longrunning__list_operations_response__descriptor) \
    , 0,NULL, (char *)protobuf_c_empty_string }


/*
 * The request message for [Operations.CancelOperation][google.longrunning.Operations.CancelOperation].
 */
struct  _Google__Longrunning__CancelOperationRequest
{
  ProtobufCMessage base;
  /*
   * The name of the operation resource to be cancelled.
   */
  char *name;
};
#define GOOGLE__LONGRUNNING__CANCEL_OPERATION_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__longrunning__cancel_operation_request__descriptor) \
    , (char *)protobuf_c_empty_string }


/*
 * The request message for [Operations.DeleteOperation][google.longrunning.Operations.DeleteOperation].
 */
struct  _Google__Longrunning__DeleteOperationRequest
{
  ProtobufCMessage base;
  /*
   * The name of the operation resource to be deleted.
   */
  char *name;
};
#define GOOGLE__LONGRUNNING__DELETE_OPERATION_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__longrunning__delete_operation_request__descriptor) \
    , (char *)protobuf_c_empty_string }


/* Google__Longrunning__Operation methods */
void   google__longrunning__operation__init
                     (Google__Longrunning__Operation         *message);
size_t google__longrunning__operation__get_packed_size
                     (const Google__Longrunning__Operation   *message);
size_t google__longrunning__operation__pack
                     (const Google__Longrunning__Operation   *message,
                      uint8_t             *out);
size_t google__longrunning__operation__pack_to_buffer
                     (const Google__Longrunning__Operation   *message,
                      ProtobufCBuffer     *buffer);
Google__Longrunning__Operation *
       google__longrunning__operation__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__longrunning__operation__free_unpacked
                     (Google__Longrunning__Operation *message,
                      ProtobufCAllocator *allocator);
/* Google__Longrunning__GetOperationRequest methods */
void   google__longrunning__get_operation_request__init
                     (Google__Longrunning__GetOperationRequest         *message);
size_t google__longrunning__get_operation_request__get_packed_size
                     (const Google__Longrunning__GetOperationRequest   *message);
size_t google__longrunning__get_operation_request__pack
                     (const Google__Longrunning__GetOperationRequest   *message,
                      uint8_t             *out);
size_t google__longrunning__get_operation_request__pack_to_buffer
                     (const Google__Longrunning__GetOperationRequest   *message,
                      ProtobufCBuffer     *buffer);
Google__Longrunning__GetOperationRequest *
       google__longrunning__get_operation_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__longrunning__get_operation_request__free_unpacked
                     (Google__Longrunning__GetOperationRequest *message,
                      ProtobufCAllocator *allocator);
/* Google__Longrunning__ListOperationsRequest methods */
void   google__longrunning__list_operations_request__init
                     (Google__Longrunning__ListOperationsRequest         *message);
size_t google__longrunning__list_operations_request__get_packed_size
                     (const Google__Longrunning__ListOperationsRequest   *message);
size_t google__longrunning__list_operations_request__pack
                     (const Google__Longrunning__ListOperationsRequest   *message,
                      uint8_t             *out);
size_t google__longrunning__list_operations_request__pack_to_buffer
                     (const Google__Longrunning__ListOperationsRequest   *message,
                      ProtobufCBuffer     *buffer);
Google__Longrunning__ListOperationsRequest *
       google__longrunning__list_operations_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__longrunning__list_operations_request__free_unpacked
                     (Google__Longrunning__ListOperationsRequest *message,
                      ProtobufCAllocator *allocator);
/* Google__Longrunning__ListOperationsResponse methods */
void   google__longrunning__list_operations_response__init
                     (Google__Longrunning__ListOperationsResponse         *message);
size_t google__longrunning__list_operations_response__get_packed_size
                     (const Google__Longrunning__ListOperationsResponse   *message);
size_t google__longrunning__list_operations_response__pack
                     (const Google__Longrunning__ListOperationsResponse   *message,
                      uint8_t             *out);
size_t google__longrunning__list_operations_response__pack_to_buffer
                     (const Google__Longrunning__ListOperationsResponse   *message,
                      ProtobufCBuffer     *buffer);
Google__Longrunning__ListOperationsResponse *
       google__longrunning__list_operations_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__longrunning__list_operations_response__free_unpacked
                     (Google__Longrunning__ListOperationsResponse *message,
                      ProtobufCAllocator *allocator);
/* Google__Longrunning__CancelOperationRequest methods */
void   google__longrunning__cancel_operation_request__init
                     (Google__Longrunning__CancelOperationRequest         *message);
size_t google__longrunning__cancel_operation_request__get_packed_size
                     (const Google__Longrunning__CancelOperationRequest   *message);
size_t google__longrunning__cancel_operation_request__pack
                     (const Google__Longrunning__CancelOperationRequest   *message,
                      uint8_t             *out);
size_t google__longrunning__cancel_operation_request__pack_to_buffer
                     (const Google__Longrunning__CancelOperationRequest   *message,
                      ProtobufCBuffer     *buffer);
Google__Longrunning__CancelOperationRequest *
       google__longrunning__cancel_operation_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__longrunning__cancel_operation_request__free_unpacked
                     (Google__Longrunning__CancelOperationRequest *message,
                      ProtobufCAllocator *allocator);
/* Google__Longrunning__DeleteOperationRequest methods */
void   google__longrunning__delete_operation_request__init
                     (Google__Longrunning__DeleteOperationRequest         *message);
size_t google__longrunning__delete_operation_request__get_packed_size
                     (const Google__Longrunning__DeleteOperationRequest   *message);
size_t google__longrunning__delete_operation_request__pack
                     (const Google__Longrunning__DeleteOperationRequest   *message,
                      uint8_t             *out);
size_t google__longrunning__delete_operation_request__pack_to_buffer
                     (const Google__Longrunning__DeleteOperationRequest   *message,
                      ProtobufCBuffer     *buffer);
Google__Longrunning__DeleteOperationRequest *
       google__longrunning__delete_operation_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__longrunning__delete_operation_request__free_unpacked
                     (Google__Longrunning__DeleteOperationRequest *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Google__Longrunning__Operation_Closure)
                 (const Google__Longrunning__Operation *message,
                  void *closure_data);
typedef void (*Google__Longrunning__GetOperationRequest_Closure)
                 (const Google__Longrunning__GetOperationRequest *message,
                  void *closure_data);
typedef void (*Google__Longrunning__ListOperationsRequest_Closure)
                 (const Google__Longrunning__ListOperationsRequest *message,
                  void *closure_data);
typedef void (*Google__Longrunning__ListOperationsResponse_Closure)
                 (const Google__Longrunning__ListOperationsResponse *message,
                  void *closure_data);
typedef void (*Google__Longrunning__CancelOperationRequest_Closure)
                 (const Google__Longrunning__CancelOperationRequest *message,
                  void *closure_data);
typedef void (*Google__Longrunning__DeleteOperationRequest_Closure)
                 (const Google__Longrunning__DeleteOperationRequest *message,
                  void *closure_data);

/* --- services --- */

typedef struct _Google__Longrunning__Operations_Service Google__Longrunning__Operations_Service;
struct _Google__Longrunning__Operations_Service
{
  ProtobufCService base;
  void (*list_operations)(Google__Longrunning__Operations_Service *service,
                          const Google__Longrunning__ListOperationsRequest *input,
                          Google__Longrunning__ListOperationsResponse_Closure closure,
                          void *closure_data);
  void (*get_operation)(Google__Longrunning__Operations_Service *service,
                        const Google__Longrunning__GetOperationRequest *input,
                        Google__Longrunning__Operation_Closure closure,
                        void *closure_data);
  void (*delete_operation)(Google__Longrunning__Operations_Service *service,
                           const Google__Longrunning__DeleteOperationRequest *input,
                           Google__Protobuf__Empty_Closure closure,
                           void *closure_data);
  void (*cancel_operation)(Google__Longrunning__Operations_Service *service,
                           const Google__Longrunning__CancelOperationRequest *input,
                           Google__Protobuf__Empty_Closure closure,
                           void *closure_data);
};
typedef void (*Google__Longrunning__Operations_ServiceDestroy)(Google__Longrunning__Operations_Service *);
void google__longrunning__operations__init (Google__Longrunning__Operations_Service *service,
                                            Google__Longrunning__Operations_ServiceDestroy destroy);
#define GOOGLE__LONGRUNNING__OPERATIONS__BASE_INIT \
    { &google__longrunning__operations__descriptor, protobuf_c_service_invoke_internal, NULL }
#define GOOGLE__LONGRUNNING__OPERATIONS__INIT(function_prefix__) \
    { GOOGLE__LONGRUNNING__OPERATIONS__BASE_INIT,\
      function_prefix__ ## list_operations,\
      function_prefix__ ## get_operation,\
      function_prefix__ ## delete_operation,\
      function_prefix__ ## cancel_operation  }
void google__longrunning__operations__list_operations(ProtobufCService *service,
                                                      const Google__Longrunning__ListOperationsRequest *input,
                                                      Google__Longrunning__ListOperationsResponse_Closure closure,
                                                      void *closure_data);
void google__longrunning__operations__get_operation(ProtobufCService *service,
                                                    const Google__Longrunning__GetOperationRequest *input,
                                                    Google__Longrunning__Operation_Closure closure,
                                                    void *closure_data);
void google__longrunning__operations__delete_operation(ProtobufCService *service,
                                                       const Google__Longrunning__DeleteOperationRequest *input,
                                                       Google__Protobuf__Empty_Closure closure,
                                                       void *closure_data);
void google__longrunning__operations__cancel_operation(ProtobufCService *service,
                                                       const Google__Longrunning__CancelOperationRequest *input,
                                                       Google__Protobuf__Empty_Closure closure,
                                                       void *closure_data);

/* --- descriptors --- */

extern const ProtobufCMessageDescriptor google__longrunning__operation__descriptor;
extern const ProtobufCMessageDescriptor google__longrunning__get_operation_request__descriptor;
extern const ProtobufCMessageDescriptor google__longrunning__list_operations_request__descriptor;
extern const ProtobufCMessageDescriptor google__longrunning__list_operations_response__descriptor;
extern const ProtobufCMessageDescriptor google__longrunning__cancel_operation_request__descriptor;
extern const ProtobufCMessageDescriptor google__longrunning__delete_operation_request__descriptor;
extern const ProtobufCServiceDescriptor google__longrunning__operations__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_google_2flongrunning_2foperations_2eproto__INCLUDED */
