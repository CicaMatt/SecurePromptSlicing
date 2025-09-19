class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person newPerson = allocatePerson();
        System.out.println("Status: " + newPerson.status);
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }
}