import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Person.getSizeofPerson()).order(ByteOrder.nativeOrder());
        buffer.putInt(0, 0); // Set status to 0
        return new Person(buffer);
    }
}

class Person {
    private static final int SIZEOF_PERSON = Integer.BYTES; // Assuming person only has an int for status
    private ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public int getStatus() {
        return buffer.getInt(0);
    }

    public static int getSizeofPerson() {
        return SIZEOF_PERSON;
    }
}