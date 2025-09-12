public class PersonAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person(0);
    }
}

class Person {
    int status;

    Person(int status) {
        this.status = status;
    }
}