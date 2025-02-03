#include <stdio.h>
#include <stdlib.h>

struct Person {
    char* name;
    int age;
    int birthYear;
};

void celebrateBirthday(struct Person* person) {
    person->age++;
}

void printPerson(struct Person* person) {
    printf("Printing info: Name %s, age %i\n", person->name, person->age);
}

int main() {
    struct Person chris;
    chris.name = "Chris";
    chris.age = 35;
    chris.birthYear = 1989;
    celebrateBirthday(&chris);
    printPerson(&chris);
}