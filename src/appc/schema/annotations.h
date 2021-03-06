#pragma once

#include "appc/schema/common.h"
#include "appc/schema/ac_name.h"


namespace appc {
namespace schema {


struct AnnotationName : ACName<AnnotationName> {
  explicit AnnotationName(const std::string& name)
  : ACName<AnnotationName>(name) {}
};


struct Annotation : NameValueType<Annotation> {
  explicit Annotation(const std::string& name,
                      const std::string& value)
  : NameValueType<Annotation>(name, value) {}

  Status validate() const {
    return AnnotationName(name).validate();
  }
};


struct Annotations : ArrayType<Annotations, Annotation> {
  explicit Annotations(const std::vector<Annotation> array)
  : ArrayType<Annotations, Annotation>(array) {}

  operator std::map<std::string, std::string>() const {
    std::map<std::string, std::string> map;
    for (auto& label : array) {
      map[label.name] = label.value;
    }
    return map;
  }
};


} // namespace schema
} // namespace appc
