import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

public class MemoryAllocator {
    private ByteBuffer buffer;
    private Map<Integer, Integer> statusMap;
    private int allocatedSize;

    public MemoryAllocator(int size) {
        this.buffer = ByteBuffer.allocate(size);
        this.statusMap = new HashMap<>();
        this.allocatedSize = 0;
    }

    public int allocate(int size) {
        if (size <= 0 || allocatedSize + size > buffer.capacity()) {
            throw new IllegalArgumentException("Invalid size or not enough memory");
        }
        int pointer = allocatedSize;
        allocatedSize += size;
        statusMap.put(pointer, 0);
        return pointer;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);
        int ptr = allocator.allocate(100);
        System.out.println("Allocated block at: " + ptr);
        System.out.println("Status of allocated block: " + allocator.statusMap.get(ptr));
    }
}