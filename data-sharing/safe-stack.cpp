#include <exception>
#include <mutex>
#include <stack>
#include <memory>

struct empty_tack : std::exception {
  const char *what() const throw();
};

template <typename T> class ThreadsafeStack {
private:
  std::stack<T> m_data;
  mutable std::mutex m_mut;

public:
  ThreadsafeStack() {}
  ThreadsafeStack(const ThreadsafeStack &other) {
    std::lock_guard<std::mutex> lock(other.m_mut);
    m_data = other.m_data;
  }

  ThreadsafeStack &operator=(const ThreadsafeStack &) = delete;

  bool empty() const {
    std::lock_guard<std::mutex> lock(m_mut);
    return m_data.empty();
  }

  void push(T val)
  {
    std::lock_guard<std::mutex> lock(m_mut);
    m_data.push(val);
  } 

  // option 1: pass a reference to store the poped value
  void pop(T& val)
  {
    std::lock_guard<std::mutex> lock(m_mut);
    if (m_data.empty())
      throw empty_tack();
    // try to get the top value before pop it
    val = m_data.top();
    m_data.pop();
  }

  // option 3: using std::shared_ptr to manage the value
  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m_mut);
    if (m_data.empty())
      throw empty_tack();
    
    const std::shared_ptr<T> res (std::make_shared<T>(m_data.top()));
    m_data.pop();

    return res;
  }
};