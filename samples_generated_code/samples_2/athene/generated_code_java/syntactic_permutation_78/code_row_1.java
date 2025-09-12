import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static ByteBuffer allocateAndSetZero(int size) {
        ByteBuffer buffer = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            buffer.put(i, (byte) 0);
        }
        return buffer;
    }

    public static void main(String[] args) {
        int size = 1024; // Example size
        ByteBuffer allocatedMemory = allocateAndSetZero(size);
        System.out.println("Memory block of " + size + " bytes allocated and set to 0.");
    }
}