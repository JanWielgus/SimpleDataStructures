/*
    Name:       FC_SinkingQueue_example.ino
    Created:	08/04/2020
    Author:     Jan Wielgus
*/

#include <SinkingQueue.h>

int test1();


void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.print("Test result: ");
    Serial.println(test1());
}

void loop()
{


}


int test1()
{
    SinkingQueue<uint16_t> testQueue(5);

    testQueue.enqueue(1);
    testQueue.enqueue(123);
    testQueue.enqueue(432);
    testQueue.enqueue(5432);
    testQueue.enqueue(2);

    if (testQueue.getQueueLength() != 5)
        return 101;
    if (testQueue.peek() != 1)
        return 1;
    testQueue.dequeue();
    if (testQueue.peek() != 123)
        return 2;
    if (testQueue.dequeue() != 123)
        return 3;

    testQueue.dequeue();
    testQueue.dequeue();
    if (testQueue.dequeue() != 2)
        return 4;
    if (testQueue.getQueueLength() != 0)
        return 5;

    testQueue.enqueue(87);
    testQueue.enqueue(543);
    testQueue.enqueue(20);

    if (testQueue.dequeue() != 87)
        return 6;

    testQueue.enqueue(592);
    if (testQueue.getQueueLength() != 3)
        return 7;

    // override last element
    testQueue.enqueue(847);
    testQueue.enqueue(54423);
    testQueue.enqueue(8337);

    if (testQueue.peek() != 20)
        return 8;
    testQueue.enqueue(999);
    if (testQueue.dequeue() != 592)
        return 9;
    if (testQueue.dequeue() != 847)
        return 10;

    testQueue.dequeue();
    testQueue.dequeue();
    testQueue.dequeue();

    if (testQueue.getQueueLength() != 0)
        return 11;


    return 0; // no errors
}
