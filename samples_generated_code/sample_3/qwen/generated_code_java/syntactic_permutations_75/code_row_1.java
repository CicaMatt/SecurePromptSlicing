class Person {
    int status;

    Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {

    public static void main(String[] args) {
        Person newPerson = allocatePerson();
        System.out.println("New person created with status: " + newPerson.status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}