/*
    Name:       FC_GrowingArray_example.ino
    Created:	08/04/2020
    Author:     Jan Wielgus
*/

#include <FC_GrowingArray.h>

// something that pretend unit tests
bool test1();


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


bool test1()
{
    FC_GrowingArrayClass<uint16_t>* testArray = new FC_GrowingArrayClass<uint16_t>;

    testArray->add(1);
    testArray->add(2);
    testArray->add(11);
    testArray->add(22);
    testArray->add(122);
    testArray->add(215);
    testArray->add(1543);
    testArray->add(532);

    if (testArray->getSize() != 8)
        return false;
    if (testArray->get(0) != 1)
        return false;
    if (testArray->get(6) != 1543)
        return false;
    if ((*testArray)[7] != 532)
        return false;
    if (testArray->getArray()[3] != 22)
        return false;


    FC_GrowingArrayClass<uint16_t> deepCopy = *testArray;
    delete testArray;
    if (deepCopy[1] != 2)
        return false;
    
}
