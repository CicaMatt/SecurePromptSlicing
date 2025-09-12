import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    private static final int SIZE_OF_PERSON = 4; // Assuming 'person' is an integer for simplicity

    public static void main(String[] args) {
        ByteBuffer memoryBlock = allocateMemory(SIZE_OF_PERSON);
        IntBuffer personBuffer = memoryBlock.asIntBuffer();
        
        // Allocating a new 'person'
        personBuffer.put(0, 123456); // Example data for the person

        int personData = personBuffer.get(0);
        System.out.println("Allocated person data: " + personData);
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}