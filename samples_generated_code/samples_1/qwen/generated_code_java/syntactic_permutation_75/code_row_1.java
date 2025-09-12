import java.nio.ByteBuffer;

public class MemoryAllocator {
    private static final int PERSON_SIZE = 16; // Assuming a simple structure with an integer status

    public static ByteBuffer allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocate(PERSON_SIZE);
        buffer.putInt(0); // Set the status to 0
        return buffer;
    }

    public static void main(String[] args) {
        ByteBuffer person = allocatePerson();
        System.out.println("Status: " + person.getInt());
    }
}