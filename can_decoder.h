/* Ryan Harbert, rwharbert@mix.wvu.edu*/

#ifndef CAN_DECODER_H_
#define CAN_DECODER_H_

#include <cstring>
#include <iostream>
#include <cstdint>
#include <thread>
#include <mutex>
#include <vector>

/*	Description: This function takes the global variables that point to the messages.
 *		It then loops through each message converting it to decimal.
 *		Once the message is converted, it is then printed out to the screen.
 *		Inside the function it locks each thread at the beginning and then
 *		unlocks it.
 */
void can_decode();

/*	Description: This function takes the global variables that point to the messages.
 *		It then updates the second byte of the message each time it is called.
 *		It takes the second byte and converts it to decimal and then increments
 *		it by 10. If the second byte goes over 255, then it modifies the first
 *		byte by 1 and then the remainder is added to the second byte. The bytes
 *		are stored back in the message as hexadecimal.
 *		Inside the function it locks each thread at the beginning and then
 *		unlocks it.
 */
void can_update();

#endif
