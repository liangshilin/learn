// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#ifndef PROTOBUF_message_2eproto__INCLUDED
#define PROTOBUF_message_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace test {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_message_2eproto();
void protobuf_AssignDesc_message_2eproto();
void protobuf_ShutdownFile_message_2eproto();

class Person;
class Person_Child;

enum Person_Gender {
  Person_Gender_NONE = 0,
  Person_Gender_MAN = 1,
  Person_Gender_WOMEN = 2
};
bool Person_Gender_IsValid(int value);
const Person_Gender Person_Gender_Gender_MIN = Person_Gender_NONE;
const Person_Gender Person_Gender_Gender_MAX = Person_Gender_WOMEN;
const int Person_Gender_Gender_ARRAYSIZE = Person_Gender_Gender_MAX + 1;

const ::google::protobuf::EnumDescriptor* Person_Gender_descriptor();
inline const ::std::string& Person_Gender_Name(Person_Gender value) {
  return ::google::protobuf::internal::NameOfEnum(
    Person_Gender_descriptor(), value);
}
inline bool Person_Gender_Parse(
    const ::std::string& name, Person_Gender* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Person_Gender>(
    Person_Gender_descriptor(), name, value);
}
// ===================================================================

class Person_Child : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:test.Person.Child) */ {
 public:
  Person_Child();
  virtual ~Person_Child();

  Person_Child(const Person_Child& from);

  inline Person_Child& operator=(const Person_Child& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Person_Child& default_instance();

  void Swap(Person_Child* other);

  // implements Message ----------------------------------------------

  inline Person_Child* New() const { return New(NULL); }

  Person_Child* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Person_Child& from);
  void MergeFrom(const Person_Child& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Person_Child* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required int32 id = 2;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:test.Person.Child)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_id();
  inline void clear_has_id();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int32 id_;
  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static Person_Child* default_instance_;
};
// -------------------------------------------------------------------

class Person : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:test.Person) */ {
 public:
  Person();
  virtual ~Person();

  Person(const Person& from);

  inline Person& operator=(const Person& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Person& default_instance();

  void Swap(Person* other);

  // implements Message ----------------------------------------------

  inline Person* New() const { return New(NULL); }

  Person* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Person& from);
  void MergeFrom(const Person& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Person* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef Person_Child Child;

  typedef Person_Gender Gender;
  static const Gender NONE =
    Person_Gender_NONE;
  static const Gender MAN =
    Person_Gender_MAN;
  static const Gender WOMEN =
    Person_Gender_WOMEN;
  static inline bool Gender_IsValid(int value) {
    return Person_Gender_IsValid(value);
  }
  static const Gender Gender_MIN =
    Person_Gender_Gender_MIN;
  static const Gender Gender_MAX =
    Person_Gender_Gender_MAX;
  static const int Gender_ARRAYSIZE =
    Person_Gender_Gender_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Gender_descriptor() {
    return Person_Gender_descriptor();
  }
  static inline const ::std::string& Gender_Name(Gender value) {
    return Person_Gender_Name(value);
  }
  static inline bool Gender_Parse(const ::std::string& name,
      Gender* value) {
    return Person_Gender_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required int32 id = 2;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // required int32 age = 3;
  bool has_age() const;
  void clear_age();
  static const int kAgeFieldNumber = 3;
  ::google::protobuf::int32 age() const;
  void set_age(::google::protobuf::int32 value);

  // optional string email = 4;
  bool has_email() const;
  void clear_email();
  static const int kEmailFieldNumber = 4;
  const ::std::string& email() const;
  void set_email(const ::std::string& value);
  void set_email(const char* value);
  void set_email(const char* value, size_t size);
  ::std::string* mutable_email();
  ::std::string* release_email();
  void set_allocated_email(::std::string* email);

  // optional .test.Person.Gender gender = 5 [default = NONE];
  bool has_gender() const;
  void clear_gender();
  static const int kGenderFieldNumber = 5;
  ::test::Person_Gender gender() const;
  void set_gender(::test::Person_Gender value);

  // repeated .test.Person.Child childer = 6;
  int childer_size() const;
  void clear_childer();
  static const int kChilderFieldNumber = 6;
  const ::test::Person_Child& childer(int index) const;
  ::test::Person_Child* mutable_childer(int index);
  ::test::Person_Child* add_childer();
  ::google::protobuf::RepeatedPtrField< ::test::Person_Child >*
      mutable_childer();
  const ::google::protobuf::RepeatedPtrField< ::test::Person_Child >&
      childer() const;

  // @@protoc_insertion_point(class_scope:test.Person)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_age();
  inline void clear_has_age();
  inline void set_has_email();
  inline void clear_has_email();
  inline void set_has_gender();
  inline void clear_has_gender();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 age_;
  ::google::protobuf::internal::ArenaStringPtr email_;
  ::google::protobuf::RepeatedPtrField< ::test::Person_Child > childer_;
  int gender_;
  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static Person* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Person_Child

// required string name = 1;
inline bool Person_Child::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Person_Child::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Person_Child::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Person_Child::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& Person_Child::name() const {
  // @@protoc_insertion_point(field_get:test.Person.Child.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person_Child::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:test.Person.Child.name)
}
inline void Person_Child::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:test.Person.Child.name)
}
inline void Person_Child::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:test.Person.Child.name)
}
inline ::std::string* Person_Child::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:test.Person.Child.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person_Child::release_name() {
  // @@protoc_insertion_point(field_release:test.Person.Child.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person_Child::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:test.Person.Child.name)
}

// required int32 id = 2;
inline bool Person_Child::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Person_Child::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Person_Child::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Person_Child::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 Person_Child::id() const {
  // @@protoc_insertion_point(field_get:test.Person.Child.id)
  return id_;
}
inline void Person_Child::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:test.Person.Child.id)
}

// -------------------------------------------------------------------

// Person

// required string name = 1;
inline bool Person::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Person::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Person::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Person::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& Person::name() const {
  // @@protoc_insertion_point(field_get:test.Person.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:test.Person.name)
}
inline void Person::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:test.Person.name)
}
inline void Person::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:test.Person.name)
}
inline ::std::string* Person::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:test.Person.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person::release_name() {
  // @@protoc_insertion_point(field_release:test.Person.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:test.Person.name)
}

// required int32 id = 2;
inline bool Person::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Person::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Person::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Person::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 Person::id() const {
  // @@protoc_insertion_point(field_get:test.Person.id)
  return id_;
}
inline void Person::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:test.Person.id)
}

// required int32 age = 3;
inline bool Person::has_age() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Person::set_has_age() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Person::clear_has_age() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Person::clear_age() {
  age_ = 0;
  clear_has_age();
}
inline ::google::protobuf::int32 Person::age() const {
  // @@protoc_insertion_point(field_get:test.Person.age)
  return age_;
}
inline void Person::set_age(::google::protobuf::int32 value) {
  set_has_age();
  age_ = value;
  // @@protoc_insertion_point(field_set:test.Person.age)
}

// optional string email = 4;
inline bool Person::has_email() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Person::set_has_email() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Person::clear_has_email() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Person::clear_email() {
  email_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_email();
}
inline const ::std::string& Person::email() const {
  // @@protoc_insertion_point(field_get:test.Person.email)
  return email_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_email(const ::std::string& value) {
  set_has_email();
  email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:test.Person.email)
}
inline void Person::set_email(const char* value) {
  set_has_email();
  email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:test.Person.email)
}
inline void Person::set_email(const char* value, size_t size) {
  set_has_email();
  email_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:test.Person.email)
}
inline ::std::string* Person::mutable_email() {
  set_has_email();
  // @@protoc_insertion_point(field_mutable:test.Person.email)
  return email_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person::release_email() {
  // @@protoc_insertion_point(field_release:test.Person.email)
  clear_has_email();
  return email_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_email(::std::string* email) {
  if (email != NULL) {
    set_has_email();
  } else {
    clear_has_email();
  }
  email_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), email);
  // @@protoc_insertion_point(field_set_allocated:test.Person.email)
}

// optional .test.Person.Gender gender = 5 [default = NONE];
inline bool Person::has_gender() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Person::set_has_gender() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Person::clear_has_gender() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Person::clear_gender() {
  gender_ = 0;
  clear_has_gender();
}
inline ::test::Person_Gender Person::gender() const {
  // @@protoc_insertion_point(field_get:test.Person.gender)
  return static_cast< ::test::Person_Gender >(gender_);
}
inline void Person::set_gender(::test::Person_Gender value) {
  assert(::test::Person_Gender_IsValid(value));
  set_has_gender();
  gender_ = value;
  // @@protoc_insertion_point(field_set:test.Person.gender)
}

// repeated .test.Person.Child childer = 6;
inline int Person::childer_size() const {
  return childer_.size();
}
inline void Person::clear_childer() {
  childer_.Clear();
}
inline const ::test::Person_Child& Person::childer(int index) const {
  // @@protoc_insertion_point(field_get:test.Person.childer)
  return childer_.Get(index);
}
inline ::test::Person_Child* Person::mutable_childer(int index) {
  // @@protoc_insertion_point(field_mutable:test.Person.childer)
  return childer_.Mutable(index);
}
inline ::test::Person_Child* Person::add_childer() {
  // @@protoc_insertion_point(field_add:test.Person.childer)
  return childer_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::test::Person_Child >*
Person::mutable_childer() {
  // @@protoc_insertion_point(field_mutable_list:test.Person.childer)
  return &childer_;
}
inline const ::google::protobuf::RepeatedPtrField< ::test::Person_Child >&
Person::childer() const {
  // @@protoc_insertion_point(field_list:test.Person.childer)
  return childer_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace test

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::test::Person_Gender> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::test::Person_Gender>() {
  return ::test::Person_Gender_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_message_2eproto__INCLUDED
