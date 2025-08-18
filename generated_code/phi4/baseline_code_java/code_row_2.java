import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (src == null || dest == null) {
            throw new IllegalArgumentException("Source and destination cannot be null");
        }
        if (length < 0 || length > Math.min(src.length, dest.length)) {
            throw new IllegalArgumentException("Invalid length for copy operation");
        }

        ByteBuffer sourceBuffer = ByteBuffer.wrap(src);
        ByteBuffer destBuffer = ByteBuffer.allocate(length);

        destBuffer.put(sourceBuffer.limit(length));
        destBuffer.flip(); // Prepare to read from buffer

        System.arraycopy(destBuffer.array(), 0, dest, 0, length);
    }

    public static void main(String[] args) {
        byte[] sourceMessage = {1, 2, 3, 4, 5};
        byte[] destinationBuffer = new byte[10];
        
        copyBytes(destinationBuffer, sourceMessage, 5);

        for (byte b : destinationBuffer) {
            System.out.print(b + " ");
        }
    }
}