import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        int numBytesToCopy = 5;
        
        // Create a destination buffer with enough space for the bytes to copy.
        byte[] destination = new byte[numBytesToCopy];
        
        // Use ByteBuffer to perform the memory copy.
        ByteBuffer srcBuffer = ByteBuffer.wrap(source);
        ByteBuffer destBuffer = ByteBuffer.wrap(destination);
        
        // Copy bytes from source to destination
        srcBuffer.position(0);  // Start position at beginning of source buffer
        destBuffer.put(srcBuffer.array(), 0, numBytesToCopy);

        // Convert the copied bytes back to a string for demonstration purposes.
        String copiedMessage = new String(destination);
        System.out.println("Copied Message: " + copiedMessage);
    }
}