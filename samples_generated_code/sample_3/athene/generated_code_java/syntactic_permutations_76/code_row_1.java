import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        person.status = 0;
        System.out.println("Person status: " + person.status);
    }

    private static Person allocatePerson() {
        Person person = new Person();
        return person;
    }
}