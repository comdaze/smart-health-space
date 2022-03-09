/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: google/protobuf/struct.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "struct.pb-c.h"
void   google__protobuf__struct__fields_entry__init
                     (Google__Protobuf__Struct__FieldsEntry         *message)
{
  static const Google__Protobuf__Struct__FieldsEntry init_value = GOOGLE__PROTOBUF__STRUCT__FIELDS_ENTRY__INIT;
  *message = init_value;
}
void   google__protobuf__struct__init
                     (Google__Protobuf__Struct         *message)
{
  static const Google__Protobuf__Struct init_value = GOOGLE__PROTOBUF__STRUCT__INIT;
  *message = init_value;
}
size_t google__protobuf__struct__get_packed_size
                     (const Google__Protobuf__Struct *message)
{
  assert(message->base.descriptor == &google__protobuf__struct__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t google__protobuf__struct__pack
                     (const Google__Protobuf__Struct *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &google__protobuf__struct__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t google__protobuf__struct__pack_to_buffer
                     (const Google__Protobuf__Struct *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &google__protobuf__struct__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Google__Protobuf__Struct *
       google__protobuf__struct__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Google__Protobuf__Struct *)
     protobuf_c_message_unpack (&google__protobuf__struct__descriptor,
                                allocator, len, data);
}
void   google__protobuf__struct__free_unpacked
                     (Google__Protobuf__Struct *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &google__protobuf__struct__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   google__protobuf__value__init
                     (Google__Protobuf__Value         *message)
{
  static const Google__Protobuf__Value init_value = GOOGLE__PROTOBUF__VALUE__INIT;
  *message = init_value;
}
size_t google__protobuf__value__get_packed_size
                     (const Google__Protobuf__Value *message)
{
  assert(message->base.descriptor == &google__protobuf__value__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t google__protobuf__value__pack
                     (const Google__Protobuf__Value *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &google__protobuf__value__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t google__protobuf__value__pack_to_buffer
                     (const Google__Protobuf__Value *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &google__protobuf__value__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Google__Protobuf__Value *
       google__protobuf__value__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Google__Protobuf__Value *)
     protobuf_c_message_unpack (&google__protobuf__value__descriptor,
                                allocator, len, data);
}
void   google__protobuf__value__free_unpacked
                     (Google__Protobuf__Value *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &google__protobuf__value__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   google__protobuf__list_value__init
                     (Google__Protobuf__ListValue         *message)
{
  static const Google__Protobuf__ListValue init_value = GOOGLE__PROTOBUF__LIST_VALUE__INIT;
  *message = init_value;
}
size_t google__protobuf__list_value__get_packed_size
                     (const Google__Protobuf__ListValue *message)
{
  assert(message->base.descriptor == &google__protobuf__list_value__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t google__protobuf__list_value__pack
                     (const Google__Protobuf__ListValue *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &google__protobuf__list_value__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t google__protobuf__list_value__pack_to_buffer
                     (const Google__Protobuf__ListValue *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &google__protobuf__list_value__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Google__Protobuf__ListValue *
       google__protobuf__list_value__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Google__Protobuf__ListValue *)
     protobuf_c_message_unpack (&google__protobuf__list_value__descriptor,
                                allocator, len, data);
}
void   google__protobuf__list_value__free_unpacked
                     (Google__Protobuf__ListValue *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &google__protobuf__list_value__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor google__protobuf__struct__fields_entry__field_descriptors[2] =
{
  {
    "key",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Google__Protobuf__Struct__FieldsEntry, key),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "value",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Google__Protobuf__Struct__FieldsEntry, value),
    &google__protobuf__value__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned google__protobuf__struct__fields_entry__field_indices_by_name[] = {
  0,   /* field[0] = key */
  1,   /* field[1] = value */
};
static const ProtobufCIntRange google__protobuf__struct__fields_entry__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor google__protobuf__struct__fields_entry__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "google.protobuf.Struct.FieldsEntry",
  "FieldsEntry",
  "Google__Protobuf__Struct__FieldsEntry",
  "google.protobuf",
  sizeof(Google__Protobuf__Struct__FieldsEntry),
  2,
  google__protobuf__struct__fields_entry__field_descriptors,
  google__protobuf__struct__fields_entry__field_indices_by_name,
  1,  google__protobuf__struct__fields_entry__number_ranges,
  (ProtobufCMessageInit) google__protobuf__struct__fields_entry__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor google__protobuf__struct__field_descriptors[1] =
{
  {
    "fields",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Google__Protobuf__Struct, n_fields),
    offsetof(Google__Protobuf__Struct, fields),
    &google__protobuf__struct__fields_entry__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned google__protobuf__struct__field_indices_by_name[] = {
  0,   /* field[0] = fields */
};
static const ProtobufCIntRange google__protobuf__struct__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor google__protobuf__struct__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "google.protobuf.Struct",
  "Struct",
  "Google__Protobuf__Struct",
  "google.protobuf",
  sizeof(Google__Protobuf__Struct),
  1,
  google__protobuf__struct__field_descriptors,
  google__protobuf__struct__field_indices_by_name,
  1,  google__protobuf__struct__number_ranges,
  (ProtobufCMessageInit) google__protobuf__struct__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor google__protobuf__value__field_descriptors[6] =
{
  {
    "null_value",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    offsetof(Google__Protobuf__Value, kind_case),
    offsetof(Google__Protobuf__Value, null_value),
    &google__protobuf__null_value__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "number_value",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_DOUBLE,
    offsetof(Google__Protobuf__Value, kind_case),
    offsetof(Google__Protobuf__Value, number_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "string_value",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    offsetof(Google__Protobuf__Value, kind_case),
    offsetof(Google__Protobuf__Value, string_value),
    NULL,
    &protobuf_c_empty_string,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "bool_value",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    offsetof(Google__Protobuf__Value, kind_case),
    offsetof(Google__Protobuf__Value, bool_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "struct_value",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Google__Protobuf__Value, kind_case),
    offsetof(Google__Protobuf__Value, struct_value),
    &google__protobuf__struct__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "list_value",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Google__Protobuf__Value, kind_case),
    offsetof(Google__Protobuf__Value, list_value),
    &google__protobuf__list_value__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned google__protobuf__value__field_indices_by_name[] = {
  3,   /* field[3] = bool_value */
  5,   /* field[5] = list_value */
  0,   /* field[0] = null_value */
  1,   /* field[1] = number_value */
  2,   /* field[2] = string_value */
  4,   /* field[4] = struct_value */
};
static const ProtobufCIntRange google__protobuf__value__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 6 }
};
const ProtobufCMessageDescriptor google__protobuf__value__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "google.protobuf.Value",
  "Value",
  "Google__Protobuf__Value",
  "google.protobuf",
  sizeof(Google__Protobuf__Value),
  6,
  google__protobuf__value__field_descriptors,
  google__protobuf__value__field_indices_by_name,
  1,  google__protobuf__value__number_ranges,
  (ProtobufCMessageInit) google__protobuf__value__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor google__protobuf__list_value__field_descriptors[1] =
{
  {
    "values",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Google__Protobuf__ListValue, n_values),
    offsetof(Google__Protobuf__ListValue, values),
    &google__protobuf__value__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned google__protobuf__list_value__field_indices_by_name[] = {
  0,   /* field[0] = values */
};
static const ProtobufCIntRange google__protobuf__list_value__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor google__protobuf__list_value__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "google.protobuf.ListValue",
  "ListValue",
  "Google__Protobuf__ListValue",
  "google.protobuf",
  sizeof(Google__Protobuf__ListValue),
  1,
  google__protobuf__list_value__field_descriptors,
  google__protobuf__list_value__field_indices_by_name,
  1,  google__protobuf__list_value__number_ranges,
  (ProtobufCMessageInit) google__protobuf__list_value__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue google__protobuf__null_value__enum_values_by_number[1] =
{
  { "NULL_VALUE", "GOOGLE__PROTOBUF__NULL_VALUE__NULL_VALUE", 0 },
};
static const ProtobufCIntRange google__protobuf__null_value__value_ranges[] = {
{0, 0},{0, 1}
};
static const ProtobufCEnumValueIndex google__protobuf__null_value__enum_values_by_name[1] =
{
  { "NULL_VALUE", 0 },
};
const ProtobufCEnumDescriptor google__protobuf__null_value__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "google.protobuf.NullValue",
  "NullValue",
  "Google__Protobuf__NullValue",
  "google.protobuf",
  1,
  google__protobuf__null_value__enum_values_by_number,
  1,
  google__protobuf__null_value__enum_values_by_name,
  1,
  google__protobuf__null_value__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
