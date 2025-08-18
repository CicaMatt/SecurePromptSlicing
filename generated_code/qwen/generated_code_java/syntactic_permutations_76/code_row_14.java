import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    private static final int PERSON_SIZE = 4; // Assuming person size is 4 bytes for simplicity

    public static void main(String[] args) {
        ByteBuffer buffer = allocateMemory(PERSON_SIZE);
        IntBuffer intBuffer = buffer.asIntBuffer();
        intBuffer.put(0, 0); // Set status to 0
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}