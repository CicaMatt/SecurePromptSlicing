import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.status);
    }

    public static Person allocatePerson() {
        ByteBuffer memoryBlock = ByteBuffer.allocateDirect(1024); // Allocate a block of memory
        return new Person(memoryBlock);
    }
}

class Person {
    int status;

    public Person(ByteBuffer memory) {
        this.status = 0; // Set the status to 0
    }
}