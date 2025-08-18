public class PersonAllocator {

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person Status: " + person.status);
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }
}

class Person {
    int status;

    Person() {
        // Constructor can be used for additional initialization if needed
    }
}