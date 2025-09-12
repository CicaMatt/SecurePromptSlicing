import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming only one integer for status
        ByteBuffer memoryBlock = allocateMemory(personSize);
        IntBuffer person = memoryBlock.asIntBuffer();
        person.put(0); // Set status to 0
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocateDirect(size);
    }
}