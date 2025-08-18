import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        // Example usage with a sample string as source
        String sourceMessage = "Hello, World!";
        byte[] destinationBuffer = new byte[sourceMessage.length()];

        copyBytes(destinationBuffer, sourceMessage.getBytes(), sourceMessage.length());
        
        System.out.println("Copied message: " + new String(destinationBuffer));
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null || numBytes <= 0 || numBytes > Math.min(dest.length, src.length)) {
            throw new IllegalArgumentException("Invalid arguments for copying bytes.");
        }
        
        ByteBuffer buffer = ByteBuffer.allocate(numBytes);
        buffer.put(src, 0, numBytes);
        buffer.flip();
        
        for (int i = 0; i < numBytes; i++) {
            dest[i] = buffer.get();
        }
    }
}