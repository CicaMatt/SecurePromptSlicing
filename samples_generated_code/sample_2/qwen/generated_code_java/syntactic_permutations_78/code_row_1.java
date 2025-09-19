import java.nio.ByteBuffer;

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.status);
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Person.SIZE);
        return new Person(buffer);
    }
}

class Person {
    public static final int SIZE = 4; // Assuming status is an integer
    private final ByteBuffer buffer;
    public int status;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
        this.status = 0;
        buffer.putInt(status);
    }
}