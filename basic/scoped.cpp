#include <memory>
#include <stdexcept>
#include <thread>
#include <utility>

class ScopedThread {
public:
  explicit ScopedThread(std::thread thd) : m_thread(std::move(thd)) {
    if (!m_thread.joinable()) {
      throw std::logic_error("not a thread");
    }
  }

  ~ScopedThread() { m_thread.join(); }

  ScopedThread(const ScopedThread &) = delete;
  ScopedThread &operator=(const ScopedThread &) = delete;

private:
  std::thread m_thread;
};