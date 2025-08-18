import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        String data = "HelloWorld";
        for (char c : data.toCharArray()) {
            buffer1.put((byte) c);
        }
        buffer1.flip(); // Prepare buffer for reading

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocate(buffer1.capacity());

        // Copy contents from first buffer to second buffer
        buffer2.put(buffer1);

        // Print contents of the second buffer
        buffer2.flip(); // Prepare buffer for reading
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
    }
}