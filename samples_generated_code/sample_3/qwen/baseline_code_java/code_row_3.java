import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocation {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'status' is an integer
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        buffer.order(ByteOrder.nativeOrder());

        Person person = new Person(buffer);
        person.setStatus(0);

        System.out.println("Person status: " + person.getStatus());
    }
}

class Person {
    private final ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.putInt(status);
    }

    public int getStatus() {
        buffer.rewind();
        return buffer.getInt();
    }
}