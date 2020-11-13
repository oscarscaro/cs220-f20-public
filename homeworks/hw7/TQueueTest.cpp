#include "Queue.h"
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
 * \struct TQueueTest
 * \defgroup TQueueTest
 * \brief Test cases for the Queue class
 */
struct TQueueTest {
  // alias
  using CQueue = Queue<char, false>;
  using IQueue = Queue<int, false>;
  using PCQueue = Queue<char, true>;
  using PIQueue = Queue<int, true>;
  
  /**
   * \brief A test function for default constructor
   */
  static void DefaultConstructorTest() {
    CQueue *cq = new CQueue();
    // check if the structure is as expected
    ASSERT(cq->_head == nullptr);
    delete cq;
    
    IQueue *iq = new IQueue();
    // check if the structure is as expected
    ASSERT(iq->_head == nullptr);
    delete iq;
    
    PCQueue *pcq = new PCQueue();
    // check if the structure is as expected
    ASSERT(pcq->_head == nullptr);
    delete pcq;
    
    PIQueue *piq = new PIQueue();
    // check if the structure is as expected
    ASSERT(piq->_head == nullptr);
    delete piq;
    
  }
   
  /**
   * \brief A test function for non-default constructor
   */
  static void NonDefaultConstructorTest() {
    CQueue *cq = new CQueue('A');
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next == nullptr);
    ASSERT(cq->_head->data == 'A');
    delete cq;
    
    IQueue *iq = new IQueue(50);
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next == nullptr);
    ASSERT(iq->_head->data == 50);
    delete iq;
    
    PCQueue *pcq = new PCQueue('A');
    // check if the structure is as expected
    ASSERT(pcq->_head != nullptr);
    ASSERT(pcq->_head->next == nullptr);
    ASSERT(pcq->_head->data == 'A');
    delete pcq;
    
    PIQueue *piq = new PIQueue(50);
    // check if the structure is as expected
    ASSERT(piq->_head != nullptr);
    ASSERT(piq->_head->next == nullptr);
    ASSERT(piq->_head->data == 50);
    delete piq;
  }
  
  /**
   * \brief A test function for copy constructor
   */
  static void CopyConstructorTest() {
    CQueue *cq = new CQueue('A');
    cq->Enqueue('B');
    cq->Enqueue('C');
    CQueue *cr = new CQueue(*cq);
    // check if the structure is as expected
    ASSERT(cr->_head != nullptr);
    ASSERT(cr->_head->next != nullptr);
    ASSERT(cr->_head->data == 'A');
    ASSERT(cr->_head->next->next != nullptr);
    ASSERT(cr->_head->next->data == 'B');
    ASSERT(cr->_head->next->next->next == nullptr);
    ASSERT(cr->_head->next->next->data == 'C');
    delete cr;
    delete cq;
    
    IQueue *iq = new IQueue(50);
    iq->Enqueue(60);
    iq->Enqueue(70);
    IQueue *ir = new IQueue(*iq);
    // check if the structure is as expected
    ASSERT(ir->_head != nullptr);
    ASSERT(ir->_head->next != nullptr);
    ASSERT(ir->_head->data == 50);
    ASSERT(ir->_head->next->next != nullptr);
    ASSERT(ir->_head->next->data == 60);
    ASSERT(ir->_head->next->next->next == nullptr);
    ASSERT(ir->_head->next->next->data == 70);
    delete ir;
    delete iq;
    
    PCQueue *pcq = new PCQueue('A');
    pcq->Enqueue('B');
    pcq->Enqueue('C');
    PCQueue *pcr = new PCQueue(*pcq);
    // check if the structure is as expected
    ASSERT(pcr->_head != nullptr);
    ASSERT(pcr->_head->next != nullptr);
    ASSERT(pcr->_head->data == 'A');
    ASSERT(pcr->_head->next->next != nullptr);
    ASSERT(pcr->_head->next->data == 'B');
    ASSERT(pcr->_head->next->next->next == nullptr);
    ASSERT(pcr->_head->next->next->data == 'C');
    delete pcr;
    delete pcq;
    
    PIQueue *piq = new PIQueue(50);
    piq->Enqueue(60);
    piq->Enqueue(70);
    PIQueue *pir = new PIQueue(*piq);
    // check if the structure is as expected
    ASSERT(pir->_head != nullptr);
    ASSERT(pir->_head->next != nullptr);
    ASSERT(pir->_head->data == 50);
    ASSERT(pir->_head->next->next != nullptr);
    ASSERT(pir->_head->next->data == 60);
    ASSERT(pir->_head->next->next->next == nullptr);
    ASSERT(pir->_head->next->next->data == 70);
    delete pir;
    delete piq;
  }
  
  /**
   * \brief A test function for assignment operator
   */
  static void OperatorAssignmentTest() {
    CQueue *cq = new CQueue('A');
    cq->Enqueue('B');
    cq->Enqueue('C');
    CQueue *cr = new CQueue('B');
    *cr = *cq;
    // check if the structure is as expected
    ASSERT(cr->_head != nullptr);
    ASSERT(cr->_head->next != nullptr);
    ASSERT(cr->_head->data == 'A');
    ASSERT(cr->_head->next->next != nullptr);
    ASSERT(cr->_head->next->data == 'B');
    ASSERT(cr->_head->next->next->next == nullptr);
    ASSERT(cr->_head->next->next->data == 'C');
    delete cr;
    delete cq;
    
    IQueue *iq = new IQueue(50);
    iq->Enqueue(60);
    iq->Enqueue(70);
    IQueue *ir = new IQueue(60);
    *ir = *iq;
    // check if the structure is as expected
    ASSERT(ir->_head != nullptr);
    ASSERT(ir->_head->next != nullptr);
    ASSERT(ir->_head->data == 50);
    ASSERT(ir->_head->next->next != nullptr);
    ASSERT(ir->_head->next->data == 60);
    ASSERT(ir->_head->next->next->next == nullptr);
    ASSERT(ir->_head->next->next->data == 70);
    delete ir;
    delete iq;
    
    PCQueue *pcq = new PCQueue('A');
    pcq->Enqueue('B');
    pcq->Enqueue('C');
    PCQueue *pcr = new PCQueue('B');
    *pcr = *pcq;
    // check if the structure is as expected
    ASSERT(pcr->_head != nullptr);
    ASSERT(pcr->_head->next != nullptr);
    ASSERT(pcr->_head->data == 'A');
    ASSERT(pcr->_head->next->next != nullptr);
    ASSERT(pcr->_head->next->data == 'B');
    ASSERT(pcr->_head->next->next->next == nullptr);
    ASSERT(pcr->_head->next->next->data == 'C');
    delete pcr;
    delete pcq;
    
    PIQueue *piq = new PIQueue(50);
    piq->Enqueue(60);
    piq->Enqueue(70);
    PIQueue *pir = new PIQueue(60);
    *pir = *piq;
    // check if the structure is as expected
    ASSERT(pir->_head != nullptr);
    ASSERT(pir->_head->next != nullptr);
    ASSERT(pir->_head->data == 50);
    ASSERT(pir->_head->next->next != nullptr);
    ASSERT(pir->_head->next->data == 60);
    ASSERT(pir->_head->next->next->next == nullptr);
    ASSERT(pir->_head->next->next->data == 70);
    delete pir;
    delete piq;
  }
  
  /**
   * \brief A test function for Enqueue
   */
  static void EnqueueTest() {
    // create a queue A->B->C
    CQueue *cq = new CQueue('A');
    cq->Enqueue('B');
    cq->Enqueue('C');
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next != nullptr);
    ASSERT(cq->_head->data == 'A');
    ASSERT(cq->_head->next->next != nullptr);
    ASSERT(cq->_head->next->data == 'B');
    ASSERT(cq->_head->next->next->next == nullptr);
    ASSERT(cq->_head->next->next->data == 'C');
    delete cq;
    
    // create a queue 50->60->70
    IQueue *iq = new IQueue(50);
    iq->Enqueue(60);
    iq->Enqueue(70);
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next != nullptr);
    ASSERT(iq->_head->data == 50);
    ASSERT(iq->_head->next->next != nullptr);
    ASSERT(iq->_head->next->data == 60);
    ASSERT(iq->_head->next->next->next == nullptr);
    ASSERT(iq->_head->next->next->data == 70);
    delete iq;
    
    // create a queue A->B->C
    PCQueue *pcq = new PCQueue('C');
    pcq->Enqueue('B');
    pcq->Enqueue('A');
    // check if the structure is as expected
    ASSERT(pcq->_head != nullptr);
    ASSERT(pcq->_head->next != nullptr);
    ASSERT(pcq->_head->data == 'A');
    ASSERT(pcq->_head->next->next != nullptr);
    ASSERT(pcq->_head->next->data == 'B');
    ASSERT(pcq->_head->next->next->next == nullptr);
    ASSERT(pcq->_head->next->next->data == 'C');
    delete pcq;
    
    // create a queue 50->60->70
    PIQueue *piq = new PIQueue(70);
    piq->Enqueue(60);
    piq->Enqueue(50);
    // check if the structure is as expected
    ASSERT(piq->_head != nullptr);
    ASSERT(piq->_head->next != nullptr);
    ASSERT(piq->_head->data == 50);
    ASSERT(piq->_head->next->next != nullptr);
    ASSERT(piq->_head->next->data == 60);
    ASSERT(piq->_head->next->next->next == nullptr);
    ASSERT(piq->_head->next->next->data == 70);
    delete piq;
  }
  
  /**
   * \brief A test function for Dequeue
   */
  static void DequeueTest() {
    // create a queue A->B->C
    CQueue *cq = new CQueue('A');
    cq->Enqueue('B');
    cq->Enqueue('C');
    // dequeue A and B
    ASSERT(cq->Dequeue() == 'A');
    ASSERT(cq->Dequeue() == 'B');
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next == nullptr);
    ASSERT(cq->_head->data == 'C');
    delete cq;
    
    // create a queue 50->60->70
    IQueue *iq = new IQueue(50);
    iq->Enqueue(60);
    iq->Enqueue(70);
    // dequeue A and B
    ASSERT(iq->Dequeue() == 50);
    ASSERT(iq->Dequeue() == 60);
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next == nullptr);
    ASSERT(iq->_head->data == 70);
    delete iq;
    
    // create a queue A->B->C
    PCQueue *pcq = new PCQueue('A');
    pcq->Enqueue('B');
    pcq->Enqueue('C');
    // dequeue A and B
    ASSERT(pcq->Dequeue() == 'A');
    ASSERT(pcq->Dequeue() == 'B');
    // check if the structure is as expected
    ASSERT(pcq->_head != nullptr);
    ASSERT(pcq->_head->next == nullptr);
    ASSERT(pcq->_head->data == 'C');
    delete pcq;
    
    // create a queue 50->60->70
    PIQueue *piq = new PIQueue(50);
    piq->Enqueue(60);
    piq->Enqueue(70);
    // dequeue A and B
    ASSERT(piq->Dequeue() == 50);
    ASSERT(piq->Dequeue() == 60);
    // check if the structure is as expected
    ASSERT(piq->_head != nullptr);
    ASSERT(piq->_head->next == nullptr);
    ASSERT(piq->_head->data == 70);
    delete piq;
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
    CQueue *cq = new CQueue('A');
    *cq << 'B' << 'C';
    // dequeue A and B
    char a, b;
    *cq >> a >> b;
    ASSERT(a == 'A');
    ASSERT(b == 'B');
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next == nullptr);
    ASSERT(cq->_head->data == 'C');
    delete cq;
    
    // create a queue 50->60->70
    IQueue *iq = new IQueue(50);
    *iq << 60 << 70;
    // dequeue A and B
    int i, j;
    *iq >> i >> j;
    ASSERT(i == 50);
    ASSERT(j == 60);
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next == nullptr);
    ASSERT(iq->_head->data == 70);
    delete iq;
    
    // create a queue A->B->C
    PCQueue *pcq = new PCQueue('A');
    *pcq << 'B' << 'C';
    // dequeue A and B
    *pcq >> a >> b;
    ASSERT(a == 'A');
    ASSERT(b == 'B');
    // check if the structure is as expected
    ASSERT(pcq->_head != nullptr);
    ASSERT(pcq->_head->next == nullptr);
    ASSERT(pcq->_head->data == 'C');
    delete pcq;
    
    // create a queue 50->60->70
    PIQueue *piq = new PIQueue(50);
    *piq << 60 << 70;
    // dequeue A and B
    *piq >> i >> j;
    ASSERT(i == 50);
    ASSERT(j == 60);
    // check if the structure is as expected
    ASSERT(piq->_head != nullptr);
    ASSERT(piq->_head->next == nullptr);
    ASSERT(piq->_head->data == 70);
    delete piq;
  }
  
  /**
   * \brief A test function for equality operator
   */
  static void OperatorEqualityTest() {
    // create two queues A->B->C
    CQueue *cq = new CQueue();
    *cq << 'A' << 'B' << 'C';
    CQueue *cr = new CQueue();
    *cr << 'A' << 'B' << 'C';
    // check if they are the same
    ASSERT(*cq == *cr);
    cq->_head->data = 'C';
    ASSERT(!(*cq == *cr));
    cq->Dequeue();
    ASSERT(!(*cq == *cr));
    delete cr;
    delete cq;
    
    // create two queues 50->60->70
    IQueue *iq = new IQueue();
    *iq << 50 << 60 << 70;
    IQueue *ir = new IQueue();
    *ir << 50 << 60 << 70;
    // check if they are the same
    ASSERT(*iq == *ir);
    iq->_head->data = 70;
    ASSERT(!(*iq == *ir));
    iq->Dequeue();
    ASSERT(!(*iq == *ir));
    delete ir;
    delete iq;
    
    // create two queues A->B->C
    PCQueue *pcq = new PCQueue();
    *pcq << 'A' << 'B' << 'C';
    PCQueue *pcr = new PCQueue();
    *pcr << 'A' << 'B' << 'C';
    // check if they are the same
    ASSERT(*pcq == *pcr);
    pcq->_head->data = 'C';
    ASSERT(!(*pcq == *pcr));
    pcq->Dequeue();
    ASSERT(!(*pcq == *pcr));
    delete pcr;
    delete pcq;
    
    // create two queues 50->60->70
    PIQueue *piq = new PIQueue();
    *piq << 50 << 60 << 70;
    PIQueue *pir = new PIQueue();
    *pir << 50 << 60 << 70;
    // check if they are the same
    ASSERT(*piq == *pir);
    piq->_head->data = 70;
    ASSERT(!(*piq == *pir));
    piq->Dequeue();
    ASSERT(!(*piq == *pir));
    delete pir;
    delete piq;
  }
  
  /**
   * \brief A test function for conatenate operator
   */
  static void OperatorConatenateTest() {
    CQueue *cq = new CQueue('A');
    cq->Enqueue('B');
    CQueue *cr = new CQueue('D');
    cr->Enqueue('C');
    CQueue *cs = new CQueue('F');
    *cs = *cq + *cr;
    // check if the structure is as expected
    ASSERT(cs->_head != nullptr);
    ASSERT(cs->_head->next != nullptr);
    ASSERT(cs->_head->data == 'A');
    ASSERT(cs->_head->next->next != nullptr);
    ASSERT(cs->_head->next->data == 'B');
    ASSERT(cs->_head->next->next->next != nullptr);
    ASSERT(cs->_head->next->next->data == 'D');
    ASSERT(cs->_head->next->next->next->next == nullptr);
    ASSERT(cs->_head->next->next->next->data == 'C');
    delete cs;
    delete cr;
    delete cq;
    
    IQueue *iq = new IQueue(50);
    iq->Enqueue(60);
    IQueue *ir = new IQueue(80);
    ir->Enqueue(70);
    IQueue *is = new IQueue(90);
    *is = *iq + *ir;
    // check if the structure is as expected
    ASSERT(is->_head != nullptr);
    ASSERT(is->_head->next != nullptr);
    ASSERT(is->_head->data == 50);
    ASSERT(is->_head->next->next != nullptr);
    ASSERT(is->_head->next->data == 60);
    ASSERT(is->_head->next->next->next != nullptr);
    ASSERT(is->_head->next->next->data == 80);
    ASSERT(is->_head->next->next->next->next == nullptr);
    ASSERT(is->_head->next->next->next->data == 70);
    delete is;
    delete ir;
    delete iq;
    
    PCQueue *pcq = new PCQueue('D');
    pcq->Enqueue('B');
    PCQueue *pcr = new PCQueue('A');
    pcr->Enqueue('C');
    PCQueue *pcs = new PCQueue('F');
    *pcs = *pcq + *pcr;
    // check if the structure is as expected
    ASSERT(pcs->_head != nullptr);
    ASSERT(pcs->_head->next != nullptr);
    ASSERT(pcs->_head->data == 'A');
    ASSERT(pcs->_head->next->next != nullptr);
    ASSERT(pcs->_head->next->data == 'B');
    ASSERT(pcs->_head->next->next->next != nullptr);
    ASSERT(pcs->_head->next->next->data == 'C');
    ASSERT(pcs->_head->next->next->next->next == nullptr);
    ASSERT(pcs->_head->next->next->next->data == 'D');
    delete pcs;
    delete pcr;
    delete pcq;
    
    PIQueue *piq = new PIQueue(80);
    piq->Enqueue(60);
    PIQueue *pir = new PIQueue(50);
    pir->Enqueue(70);
    PIQueue *pis = new PIQueue(90);
    *pis = *piq + *pir;
    // check if the structure is as expected
    ASSERT(pis->_head != nullptr);
    ASSERT(pis->_head->next != nullptr);
    ASSERT(pis->_head->data == 50);
    ASSERT(pis->_head->next->next != nullptr);
    ASSERT(pis->_head->next->data == 60);
    ASSERT(pis->_head->next->next->next != nullptr);
    ASSERT(pis->_head->next->next->data == 70);
    ASSERT(pis->_head->next->next->next->next == nullptr);
    ASSERT(pis->_head->next->next->next->data == 80);
    delete pis;
    delete pir;
    delete piq;
  }
  
  /**
   * \brief A test function for stream insertion operator
   */
  static void OperatorStreamInsertionTest() {
    // create a queue A->B->C
    CQueue *cq = new CQueue();
    *cq << 'A' << 'B' << 'C';
    std::stringstream css;
    css << *cq;
    ASSERT(css.str() == "A -> B -> C -> NULL\n");
    delete cq;
    
    // create a queue 50->60->70
    IQueue *iq = new IQueue();
    *iq << 50 << 60 << 70;
    std::stringstream iss;
    iss << *iq;
    ASSERT(iss.str() == "50 -> 60 -> 70 -> NULL\n");
    delete iq;
    
    cout << "Stream insertion operator tests passed" << endl; 
    
    // create a queue A->B->C
    PCQueue *pcq = new PCQueue();
    *pcq << 'C' << 'B' << 'A';
    std::stringstream pcss;
    pcss << *pcq;
    ASSERT(pcss.str() == "A -> B -> C -> NULL\n");
    delete pcq;
    
    // create a queue 50->60->70
    PIQueue *piq = new PIQueue();
    *piq << 70 << 60 << 50;
    std::stringstream piss;
    piss << *piq;
    ASSERT(piss.str() == "50 -> 60 -> 70 -> NULL\n");
    delete piq;
  }
};

// call our test functions in the main
int main(int, char* argv[]) {
  cout << "Testing Queue" << endl;
  // register a seg fault hanlder
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);
  
  TQueueTest::DefaultConstructorTest();
  TQueueTest::NonDefaultConstructorTest();
  TQueueTest::CopyConstructorTest();
  TQueueTest::OperatorAssignmentTest();
  TQueueTest::EnqueueTest();
  TQueueTest::DequeueTest();
  TQueueTest::OperatorInsertionTest();
  TQueueTest::OperatorExtractionTest();
  TQueueTest::OperatorEqualityTest();
  TQueueTest::OperatorConatenateTest();
  TQueueTest::OperatorStreamInsertionTest();
}
