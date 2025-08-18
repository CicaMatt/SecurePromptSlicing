import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {

    private static final int PERSON_SIZE = 4; // Assuming status is an integer

    public static void main(String[] args) {
        ByteBuffer memoryBlock = allocateMemory(PERSON_SIZE);
        IntBuffer person = memoryBlock.asIntBuffer();
        person.put(0, 1); // Setting status to 1 (or any other value you wish)
        
        System.out.println("Status: " + person.get(0));
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}