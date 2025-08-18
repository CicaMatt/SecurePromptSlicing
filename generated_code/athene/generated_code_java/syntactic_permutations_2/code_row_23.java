import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyMemory(ByteBuffer dest, ByteBuffer src, int numBytes) {
        if (dest == null || src == null) {
            throw new IllegalArgumentException("Destination and source buffers must not be null.");
        }
        if (numBytes < 0) {
            throw new IllegalArgumentException("Number of bytes to copy must be non-negative.");
        }

        int originalDestPosition = dest.position();
        int originalSrcPosition = src.position();

        while (numBytes > 0 && src.hasRemaining() && dest.hasRemaining()) {
            int bytesToCopy = Math.min(numBytes, Math.min(src.remaining(), dest.remaining()));
            src.get(dest.array(), dest.arrayOffset() + dest.position(), bytesToCopy);
            numBytes -= bytesToCopy;
            dest.position(dest.position() + bytesToCopy);
        }

        dest.position(originalDestPosition + (originalSrcPosition - src.position()));
    }

    public static void main(String[] args) {
        ByteBuffer dest = ByteBuffer.allocate(10);
        ByteBuffer src = ByteBuffer.wrap(new byte[]{1, 2, 3, 4, 5});

        copyMemory(dest, src, 3);

        for (int i = 0; i < dest.position(); i++) {
            System.out.print(dest.get(i) + " ");
        }
    }
}