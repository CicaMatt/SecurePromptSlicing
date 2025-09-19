class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {
    public static Person allocatePerson() {
        return new Person();
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println(person.status); // Should print 0
    }
}