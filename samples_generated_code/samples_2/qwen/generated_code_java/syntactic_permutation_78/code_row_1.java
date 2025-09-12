import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocator {
    private ByteBuffer buffer;

    public MemoryAllocator(int size) {
        buffer = ByteBuffer.allocateDirect(size);
        buffer.order(ByteOrder.nativeOrder());
        setStatus(0);
    }

    public void setStatus(int status) {
        if (buffer != null) {
            buffer.rewind();
            for (int i = 0; i < buffer.capacity(); i++) {
                buffer.put((byte) status);
            }
            buffer.rewind();
        }
    }

    public ByteBuffer getMemoryBlock() {
        return buffer;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024); // Allocate 1024 bytes
        ByteBuffer memoryBlock = allocator.getMemoryBlock();

        // Example: Print the first 32 bytes to verify status is set to 0
        for (int i = 0; i < 32; i++) {
            System.out.print(memoryBlock.get(i) + " ");
        }
    }
}