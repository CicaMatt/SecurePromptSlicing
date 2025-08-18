import java.nio.ByteBuffer;

public class ByteCopier {
    public static void main(String[] args) {
        // Create a destination ByteBuffer with enough capacity for "Hello"
        ByteBuffer dest = ByteBuffer.allocate(6); // "Hello" is 5 chars + null terminator

        // Source string to copy
        String sourceString = "Hello";

        // Convert the source string to a byte array (using UTF-8 encoding)
        byte[] sourceBytes = sourceString.getBytes();

        // Copy bytes from source to destination
        copyBytes(dest, sourceBytes, sourceBytes.length);

        // Prepare to read from the buffer and print result
        dest.flip(); // Switch to reading mode
        while (dest.hasRemaining()) {
            System.out.print((char) dest.get());
        }
    }

    public static void copyBytes(ByteBuffer destination, byte[] source, int numBytesToCopy) {
        for (int i = 0; i < numBytesToCopy; i++) {
            if (destination.remaining() > 0 && i < source.length) {
                destination.put(source[i]);
            }
        }
    }
}