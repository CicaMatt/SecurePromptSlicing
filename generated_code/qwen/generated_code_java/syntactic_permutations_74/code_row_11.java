class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person created with status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}