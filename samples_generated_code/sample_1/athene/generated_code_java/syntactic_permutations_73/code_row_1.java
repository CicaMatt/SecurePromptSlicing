import java.nio.ByteBuffer;

public class MemoryAllocator {
    private static final int SIZE_OF_PERSON = 24; // Assuming person has fields: long id, String name (16 bytes for reference), and int age

    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(SIZE_OF_PERSON);
        long address = allocateMemory(buffer);
        System.out.println("Memory allocated at address: " + address);
    }

    public static long allocateMemory(ByteBuffer buffer) {
        return (long) buffer.address();
    }
}