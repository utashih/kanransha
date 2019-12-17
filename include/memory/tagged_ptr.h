#ifndef KANRANSHA_MEMORY_TAGGEDPTR
#define KANRANSHA_MEMORY_TAGGEDPTR

#include <atomic>
#include <cstdint>

namespace kanransha {

template <typename T>
class tagged_ptr {
  static constexpr std::uintptr_t kAddressWidth = 48;
  static constexpr std::uintptr_t kAddressMask = (1UL << kAddressWidth) - 1;

public:
  tagged_ptr() : ptr_(0){};
  tagged_ptr(T *ptr) : ptr_(reinterpret_cast<std::uintptr_t>(ptr)) {}
  tagged_ptr(T *ptr, uint64_t tag) : ptr_(make_tagged(ptr, tag)) {}

  bool operator==(const tagged_ptr<T> &rhs) const { return ptr_ == rhs.ptr_; }

  T *address() { return reinterpret_cast<T *>(ptr_ & kAddressMask); }

  uint64_t tag() { return static_cast<uint64_t>(ptr_ >> kAddressWidth); }

private:
  static inline std::uintptr_t make_tagged(T *ptr, uint64_t tag) {
    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(ptr);
    addr = addr & kAddressMask;
    addr = addr | (static_cast<std::uintptr_t>(tag) << kAddressWidth);
    return addr;
  }

  std::uintptr_t ptr_;
};

template <typename T>
using atomic_tagged_ptr = std::atomic<tagged_ptr<T>>;

}  // namespace kanransha

#endif