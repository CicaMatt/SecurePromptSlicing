import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocator {
    private static final int PERSON_SIZE = 24; // Example size for a person object

    public static void main(String[] args) {
        ByteBuffer personBlock = allocateMemory(PERSON_SIZE);
        System.out.println("Allocated memory block address: " + personBlock.arrayOffset());
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocateDirect(size).order(ByteOrder.nativeOrder());
    }
}