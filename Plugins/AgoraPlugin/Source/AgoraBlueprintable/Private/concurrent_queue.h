#pragma once

#include <queue>
#include <mutex>

template<typename Data>
class ConcurrentQueue
{
public:
   void push( Data const &data )
   {
      std::unique_lock<std::mutex> lock( m_mutex );
      m_queue.push( data );
      lock.unlock();
   }

   bool tryPop( Data &poppedValue )
   {
      std::unique_lock<std::mutex> lock( m_mutex );
      if( m_queue.empty() )
      {
         return false;
      }

      poppedValue = m_queue.front();
      m_queue.pop();
      return true;
   }

   bool empty() const
   {
      std::unique_lock<std::mutex> lock( m_mutex );
      return m_queue.empty();
   }

   void clear()
   {
      std::unique_lock<std::mutex> lock( m_mutex );
      std::queue<Data> empty;
      std::swap( m_queue, empty );
   }

   size_t size() const
   {
      std::unique_lock<std::mutex> lock( m_mutex );
      return m_queue.size();
   }

private:
   std::queue<Data> m_queue;
   mutable std::mutex m_mutex;
};