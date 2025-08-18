import java.nio.ByteBuffer;

public class MemoryAllocator {
    private ByteBuffer buffer;
    private int[] status;

    public MemoryAllocator(int size) {
        this.buffer = ByteBuffer.allocate(size);
        this.status = new int[1];
        status[0] = 0;
    }

    public long allocate(int size) {
        if (status[0] == 0 && buffer.position() + size <= buffer.capacity()) {
            long address = buffer.position();
            buffer.position(buffer.position() + size);
            return address;
        }
        return -1; // Allocation failed
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);
        long pointer = allocator.allocate(100);
        System.out.println("Allocated memory at: " + pointer);
    }
}