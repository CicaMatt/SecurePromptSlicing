import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        int numBytesToCopy = 5;
        
        ByteBuffer buffer = allocateByteBuffer(numBytesToCopy);
        copyBytes(source, buffer, numBytesToCopy);

        // Print copied bytes for verification
        System.out.println(new String(buffer.array(), 0, numBytesToCopy));
    }

    public static void copyBytes(byte[] source, ByteBuffer destinationBuffer, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            destinationBuffer.put(source[i]);
        }
    }

    private static ByteBuffer allocateByteBuffer(int capacity) {
        return ByteBuffer.allocate(capacity);
    }
}