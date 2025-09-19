import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class PersonAllocator {
    private static final int PERSON_SIZE = Integer.BYTES; // Assuming 'status' is an integer

    public static ByteBuffer allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocate(PERSON_SIZE);
        buffer.order(ByteOrder.nativeOrder());
        buffer.putInt(0); // Set the status field to 0
        buffer.rewind();
        return buffer;
    }

    public static void main(String[] args) {
        ByteBuffer personBuffer = allocatePerson();
        System.out.println("Status: " + personBuffer.getInt()); // Should print Status: 0
    }
}