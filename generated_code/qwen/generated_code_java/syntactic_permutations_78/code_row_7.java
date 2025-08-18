import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming person only has an integer status field
        ByteBuffer buffer = ByteBuffer.allocate(personSize);
        allocatePerson(buffer);
        System.out.println("Person status: " + buffer.getInt(0));
    }

    private static void allocatePerson(ByteBuffer memory) {
        memory.putInt(0); // Set status to 0
    }
}