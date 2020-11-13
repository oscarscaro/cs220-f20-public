#include "CQueue.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

#ifndef ASSERT
#include <csignal>  // signal handler 
#include <cstring>  // memset
#include <string>
char programName[128];

void segFaultHandler(int, siginfo_t*, void *context) {
  char cmdbuffer[1024];
  char resultbuffer[128];
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName, (void*)((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]);
  std::string result = "";
  FILE* pipe = popen(cmdbuffer, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
    while (fgets(resultbuffer, sizeof resultbuffer, pipe) != NULL) {
      result += resultbuffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  cout << "Segmentation fault occured in " << result;  
  ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] +=2 ; // skip the seg fault
}

#define ASSERT(cond) if (!(cond)) { \
    cout << "failed ASSERT " << #cond << " at line " << __LINE__ << endl; \
  } else { \
    cout << __func__ << " - (" << #cond << ")" << " passed!" << endl; \
  }
#endif

/**
 * \struct CQueueTest
 * \defgroup CQueueTest
 * \brief Test cases for the CQueue class
 */
struct CQueueTest {
  /**
   * \brief A test function for default constructor
   */
  static void DefaultConstructorTest() {
    CQueue *q = new CQueue();
    // check if the structure is as expected
    ASSERT(q->_head == nullptr);
    delete q;
  }
   
  /**
   * \brief A test function for non-default constructor
   */
  static void NonDefaultConstructorTest() {
    CQueue *q = new CQueue('A');
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next == nullptr);
    ASSERT(q->_head->data == 'A');
    delete q;
  }
  
  /**
   * \brief A test function for copy constructor
   */
  static void CopyConstructorTest() {
    CQueue *q = new CQueue('A');
    q->Enqueue('B');
    q->Enqueue('C');
    CQueue *r = new CQueue(*q);
    // check if the structure is as expected
    ASSERT(r->_head != nullptr);
    ASSERT(r->_head->next != nullptr);
    ASSERT(r->_head->data == 'A');
    ASSERT(r->_head->next->next != nullptr);
    ASSERT(r->_head->next->data == 'B');
    ASSERT(r->_head->next->next->next == nullptr);
    ASSERT(r->_head->next->next->data == 'C');
    delete r;
    delete q;
    cout << "Copy constructor tests passed" << endl;
  }
  
  /**
   * \brief A test function for assignment operator
   */
  static void OperatorAssignmentTest() {
    CQueue *q = new CQueue('A');
    q->Enqueue('B');
    q->Enqueue('C');
    CQueue *r = new CQueue('B');
    *r = *q;
    // check if the structure is as expected
    ASSERT(r->_head != nullptr);
    ASSERT(r->_head->next != nullptr);
    ASSERT(r->_head->data == 'A');
    ASSERT(r->_head->next->next != nullptr);
    ASSERT(r->_head->next->data == 'B');
    ASSERT(r->_head->next->next->next == nullptr);
    ASSERT(r->_head->next->next->data == 'C');
    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for Enqueue
   */
  static void EnqueueTest() {
    // create a queue A->B->C
    CQueue *q = new CQueue('A');
    q->Enqueue('B');
    q->Enqueue('C');
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next != nullptr);
    ASSERT(q->_head->data == 'A');
    ASSERT(q->_head->next->next != nullptr);
    ASSERT(q->_head->next->data == 'B');
    ASSERT(q->_head->next->next->next == nullptr);
    ASSERT(q->_head->next->next->data == 'C');
    delete q;
  }
  
  /**
   * \brief A test function for Dequeue
   */
  static void DequeueTest() {
    // create a queue A->B->C
    CQueue *q = new CQueue('A');
    q->Enqueue('B');
    q->Enqueue('C');
    // dequeue A and B
    ASSERT(q->Dequeue() == 'A');
    ASSERT(q->Dequeue() == 'B');
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next == nullptr);
    ASSERT(q->_head->data == 'C');
    delete q;
  }
  
  /**
   * \brief A test function for insertion operator
   */
  static void OperatorInsertionTest() {
    // create a queue A->B->C
    CQueue *q = new CQueue();
    *q << 'A' << 'B' << 'C';
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next != nullptr);
    ASSERT(q->_head->data == 'A');
    ASSERT(q->_head->next->next != nullptr);
    ASSERT(q->_head->next->data == 'B');
    ASSERT(q->_head->next->next->next == nullptr);
    ASSERT(q->_head->next->next->data == 'C');
    delete q;
  }
  
  /**
   * \brief A test function for extraction operator
   */
  static void OperatorExtractionTest() {
    // create a queue A->B->C
    CQueue *q = new CQueue();
    *q << 'A' << 'B' << 'C';
    // dequeue A and B
    char a, b;
    *q >> a >> b;
    ASSERT(a == 'A');
    ASSERT(b == 'B');
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next == nullptr);
    ASSERT(q->_head->data == 'C');
    delete q;
  }
  
  /**
   * \brief A test function for equality operator
   */
  static void OperatorEqualityTest() {
    // create two queues A->B->C
    CQueue *q = new CQueue();
    *q << 'A' << 'B' << 'C';
    CQueue *r = new CQueue();
    *r << 'A' << 'B' << 'C';
    // check if they are the same
    ASSERT(*q == *r);
    q->_head->data = 'C';
    ASSERT(!(*q == *r));
    q->Dequeue();
    ASSERT(!(*q == *r));
    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for conatenate operator
   */
  static void OperatorConatenateTest() {
    CQueue *q = new CQueue('A');
    q->Enqueue('B');
    CQueue *r = new CQueue('D');
    r->Enqueue('C');
    CQueue *s = new CQueue('F');
    *s = *q + *r;
    // check if the structure is as expected
    ASSERT(s->_head != nullptr);
    ASSERT(s->_head->next != nullptr);
    ASSERT(s->_head->data == 'A');
    ASSERT(s->_head->next->next != nullptr);
    ASSERT(s->_head->next->data == 'B');
    ASSERT(s->_head->next->next->next != nullptr);
    ASSERT(s->_head->next->next->data == 'D');
    ASSERT(s->_head->next->next->next->next == nullptr);
    ASSERT(s->_head->next->next->next->data == 'C');
    delete s;
    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for stream insertion operator
   */
  static void OperatorStreamInsertionTest() {
    // create a queue A->B->C
    CQueue *q = new CQueue();
    *q << 'A' << 'B' << 'C';
    std::stringstream ss;
    ss << *q;
    ASSERT(ss.str() == "A -> B -> C -> NULL\n");
    delete q;
  }
};

// call our test functions in the main
int main(int, char* argv[]) {
  cout << "Testing CQueue" << endl;
  // register a seg fault hanlder
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);
  
  CQueueTest::DefaultConstructorTest();
  CQueueTest::NonDefaultConstructorTest();
  CQueueTest::CopyConstructorTest();
  CQueueTest::OperatorAssignmentTest();
  CQueueTest::EnqueueTest();
  CQueueTest::DequeueTest();
  CQueueTest::OperatorInsertionTest();
  CQueueTest::OperatorExtractionTest();
  CQueueTest::OperatorEqualityTest();
  CQueueTest::OperatorConatenateTest();
  CQueueTest::OperatorStreamInsertionTest();
}
