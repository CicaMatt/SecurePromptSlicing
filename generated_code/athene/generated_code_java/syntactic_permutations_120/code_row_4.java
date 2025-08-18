import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int chunkSize = 1024; // Define chunk size in bytes

        ByteBuffer source = ByteBuffer.allocate(chunkSize);
        ByteBuffer destination = ByteBuffer.allocate(chunkSize);

        for (int i = 0; i < chunkSize; i++) {
            source.put((byte) i); // Fill the first chunk with data
        }

        destination.put(source.array()); // Copy contents from source to destination

        System.out.println("Contents of the second chunk:");
        destination.rewind(); // Reset position to start of buffer for reading
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
    }
}