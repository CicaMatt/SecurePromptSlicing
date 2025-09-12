import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {

    public static void main(String[] args) {
        byte[] sourceMessage = "This is a test message.".getBytes();
        ByteBuffer buffer = ByteBuffer.allocate(sourceMessage.length);

        copyBytes(buffer, sourceMessage, sourceMessage.length);
        
        System.out.println("Copied bytes to buffer: " + Arrays.toString(buffer.array()));
    }

    public static void copyBytes(ByteBuffer destination, byte[] source, int numBytes) {
        if (destination.remaining() < numBytes) {
            throw new IllegalArgumentException("Destination buffer does not have enough space");
        }
        for (int i = 0; i < numBytes; i++) {
            destination.put(source[i]);
        }
    }
}