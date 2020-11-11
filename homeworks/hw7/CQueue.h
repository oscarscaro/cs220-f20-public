#ifndef CQUEUE_HW7_H__
#define CQUEUE_HW7_H__

// ios forward declaration
#include <iosfwd>

/**
 * \class CQueue
 * \defgroup CQueue
 * \breif A character queue.
 */
class CQueue {
public:
  /**
   * \brief The default constructor - create an empty queue
   */
  CQueue();
  
  /**
   * \brief A constructor takes a char input to create a queue
   * \param ch The input character
   */
  CQueue(const char& ch);
  
  /**
   * \brief Copy constructor
   * \param rhs A constant reference to the input CQueue object
   */ 
  CQueue(const CQueue& rhs);
  
  /**
   * \brief Overloaded operator= to assign a queue to another queue
   * \param rhs A reference to the input CQueue object
   */
  void operator=(const CQueue& rhs); 
  
  /**
   * \brief The destructor - release memories if needed
   */
  ~CQueue();
  
  /**
   * \brief A function to enqueue a character to the queue
   * \param ch The input character to add to the queue
   */
  void Enqueue(const char& ch);

  /**
   * \brief A function to dequeue a character from the queue
   * \return The first character in the queue
   */
  char Dequeue();
  
  /**
   * \brief Overloaded operator<< to enqueue
   * \param ch The input character to add to the queue
   * \return A reference to the CQueue object
   */
  CQueue& operator<<(const char& ch);
  
  /**
   * \brief Overloaded operator>> to dequeue
   * \param ch A reference to the output character
   * \return A reference to the CQueue object
   */
  CQueue& operator>>(char& ch);
  
  /**
   * \brief Overloaded operator== to check if two queues are the same
   * \param rhs A reference to a CQueue object to compare
   * \return true if two CQueues are the same node by node, else false
   */
  bool operator==(const CQueue &rhs) const;
  
  /**
   * \brief Overloaded operator+ to concatenate two queues
   */
  CQueue operator+(const CQueue& rhs) const;
  
  /**
   * \brief Overloaded output stream operator<< to print the queue in 
   * this format data1 -> data2 -> ... -> datax -> NULL<newline>
   *   e.g. if we have a queue with three elements 'a', 'b', 'c'
   *        it will print "a -> b -> c -> NULL\n"
   * \param os A reference to the output stream object
   * \param q A constant reference to the input CQueue object
   * \return A reference to the output stream object
   */
  friend std::ostream& operator<<(std::ostream& os, const CQueue& q);
  
private:
  /// friend CQueueTest class to allow the test class access the private data
  friend class CQueueTest;
  
  /**
   * \struct Node_
   * \breif A private structure to represent a node in a queue
   */
  struct _Node {
    char data;    ///< A character node data
    _Node *next;  ///< A pointer to the next node. nullptr if it is the end node
  };

  _Node *_head;   ///< a pointer to the head node of the queue
};

#endif // CQUEUE_HW7_H__
