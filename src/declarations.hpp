#pragma once

namespace lua {
  // Main interface class
  struct state;

  // Generic lua entity (primitive types, tables, functions) holder
  template <typename policy_t>
  struct entity;
  
  // Type adapter, maps C++ type to corresponding entity type.
  template <typename T>
  struct type_policy;

  // Iterable vector-like entities
  template <typename T>
  struct vector_element;
}
