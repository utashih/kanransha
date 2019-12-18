#ifndef KANRANSHA_MEMORY_MANAGER
#define KANRANSHA_MEMORY_MANAGER

#include <cstddef>

namespace kanransha {

template <typename derived_t>
class memory_manager_base {
public:
  void *allocate(size_t size, size_t alignment) {
    return get_derived()->allocate_impl(size, alignment);
  }

  template <typename T>
  T *allocate(size_t num = 1) {
    return static_cast<T *>(allocate(num * sizeof(T), alignof(T)));
  }

  void retire(void *ptr) { return get_derived()->retire_impl(ptr); }

  void protect() { return get_derived()->protect_impl(); }

  void unprotect() { return get_derived()->unprotect_impl(); }

private:
  derived_t *get_derived() { return static_cast<derived_t *>(this); }
};

template <typename memory_manager_t>
class memory_guard {
public:
  memory_guard(memory_manager_t *manager) : manager_(manager) {
    manager_->protect();
  }

  ~memory_guard() { manager_->unprotect(); }

private:
  memory_guard(const memory_guard &) = delete;
  memory_guard &operator=(const memory_guard &) = delete;

  memory_manager_t *manager_;
};

}  // namespace kanransha

#endif