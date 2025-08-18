import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Person.SIZE);
        buffer.order(ByteOrder.nativeOrder());

        Person person = new Person(buffer);
        person.setStatus(0);

        return person;
    }
}

class Person {
    public static final int SIZE = 4; // Assuming status is an integer

    private final ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public int getStatus() {
        return buffer.getInt(0);
    }

    public void setStatus(int status) {
        buffer.putInt(0, status);
    }
}