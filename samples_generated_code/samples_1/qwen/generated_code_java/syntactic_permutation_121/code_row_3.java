import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Put some data into the first chunk
        String data = "HelloWorld";
        for (char c : data.toCharArray()) {
            buffer1.put((byte) c);
        }
        buffer1.flip();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);
        buffer2.flip();

        // Print the contents of the second chunk
        System.out.println("Contents of second chunk after copy:");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();
        buffer2.rewind();

        // Free the memory allocated to the first chunk
        // In Java, memory is managed by the garbage collector, so we just clear the reference
        buffer1 = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of second chunk after freeing first chunk:");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();
        buffer2.rewind();

        // Free the memory allocated to the second chunk
        // Again, we just clear the reference
        buffer2 = null;
    }
}