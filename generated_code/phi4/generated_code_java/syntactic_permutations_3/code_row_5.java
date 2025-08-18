import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Create a byte array representing the string "Hello"
        String sourceString = "Hello";
        ByteBuffer sourceBuffer = ByteBuffer.wrap(sourceString.getBytes());

        // Create a destination buffer with enough space for the bytes
        byte[] destinationArray = new byte[sourceBuffer.remaining()];
        ByteBuffer destinationBuffer = ByteBuffer.wrap(destinationArray);

        // Copy bytes from source to destination
        copyBytes(destinationBuffer, sourceBuffer, sourceBuffer.remaining());

        // Print the contents of the destination buffer as a string
        System.out.println(new String(destinationBuffer.array()));
    }

    public static void copyBytes(ByteBuffer dest, ByteBuffer src, int numBytes) {
        while (numBytes > 0 && src.hasRemaining()) {
            byte b = src.get();
            if (dest.remaining() > 0) {
                dest.put(b);
            }
            numBytes--;
        }
    }
}