import java.nio.ByteBuffer;

public class MemoryAllocator {
    private ByteBuffer buffer;

    public MemoryAllocator(int capacity) {
        this.buffer = ByteBuffer.allocate(capacity);
    }

    public long allocatePerson() {
        int personSize = sizeofPerson();
        if (buffer.remaining() < personSize) {
            throw new OutOfMemoryError("Not enough space to allocate a person");
        }
        long address = buffer.position();
        buffer.position(buffer.position() + personSize);
        return address;
    }

    private int sizeofPerson() {
        // Assuming person has 3 fields: long, int, and double
        return Long.BYTES + Integer.BYTES + Double.BYTES;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);
        long address = allocator.allocatePerson();
        System.out.println("Allocated person at address: " + address);
    }
}