public class BufferAllocator {

    private byte[] buf;

    public void allocateBuffer() {
        this.buf = new byte[1024];
    }

    public void storeData(byte data, int index) {
        if (index >= 0 && index < buf.length) {
            buf[index] = data;
        } else {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + buf.length);
        }
    }

    public static void main(String[] args) {
        BufferAllocator allocator = new BufferAllocator();
        allocator.allocateBuffer();

        // Example of storing a byte value in the buffer
        allocator.storeData((byte) 123, 0); // Storing value at index 0

        System.out.println("Stored data: " + allocator.buf[0]);
    }
}