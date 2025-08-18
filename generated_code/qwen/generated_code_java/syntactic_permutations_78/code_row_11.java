import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    private ByteBuffer buffer;

    public MemoryAllocator(int capacity) {
        this.buffer = ByteBuffer.allocate(capacity);
    }

    public int allocatePerson() {
        if (buffer.remaining() < Integer.BYTES * 2) {
            throw new OutOfMemoryError("Not enough memory to allocate a person");
        }
        IntBuffer intBuffer = buffer.asIntBuffer();
        intBuffer.put(0); // status
        int position = buffer.position();
        buffer.position(buffer.position() + Integer.BYTES * 2);
        return position;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);
        int personPosition = allocator.allocatePerson();
        System.out.println("Person allocated at position: " + personPosition);
    }
}