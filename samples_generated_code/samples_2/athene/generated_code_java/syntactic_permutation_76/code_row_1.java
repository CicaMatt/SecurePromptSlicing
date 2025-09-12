import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocator {
    public static Person allocateMemory() {
        Person person = new Person();
        person.status = 0;
        return person;
    }

    public static void main(String[] args) {
        Person p = allocateMemory();
        System.out.println("Status: " + p.status);
    }
}