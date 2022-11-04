/* CS270 
 *
 * Author: Your name here
 * Date:   2/12/2020
 */

#include "struct.h"
#include<stdio.h>
#include <stdlib.h>

/********** FUNCTION DEFINITIONS **********************************************/

void readStudentAndEnroll(Student **slot)
{
  Student *temp = malloc(sizeof(Student *));
  scanf("Enter a name: %s", temp->firstName);
  scanf("Enter quality points: %f", &(temp->qualityPoints));
  scanf("Enter num credits:%d", &(temp->numCredits));
  *slot = temp;
}

void displayStudent(Student s)
{
	printf("%s, %.2f",s.firstName,s.qualityPoints/s.numCredits);
}
