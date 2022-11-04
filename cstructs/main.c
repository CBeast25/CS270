 /** @mainpage 
   *  \htmlinclude "STRUCTS.html"
   */
/* CS270 
 *
 * Author: Your name here
 * Date:   2/12/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

int main(int argc, const char **argv)
{
  // TODO: Complete the main function
  int numStudents = 0;
  printf("work");
  scanf("How many students? %d", &numStudents);

  ClassRoster roster;
  roster.numStudents = numStudents;
  roster.students = calloc(numStudents, sizeof(Student *));

  for(int i = 0; i < roster.numStudents; i++) {
      readStudentAndEnroll(roster.students+i);
  }

  for(int i = 0; i < roster.numStudents; i++) {
      displayStudent(*(roster.students[i]));
      free(roster.students[i]);
  }

  free(roster.students);
  return 0;
}
