import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        ByteBuffer destination = ByteBuffer.allocate(4);
        ByteBuffer source = ByteBuffer.allocate(4);
        int numberToCopy = 12345;

        source.putInt(numberToCopy);
        source.flip();

        copyNumber(destination, source, numberToCopy);

        System.out.println("Copied Number: " + destination.getInt());
    }

    public static void copyNumber(ByteBuffer destination, ByteBuffer source, int number) {
        if (source.remaining() < Integer.BYTES || destination.remaining() < Integer.BYTES) {
            throw new IllegalArgumentException("Source or Destination buffer is too small.");
        }
        source.rewind();
        destination.putInt(source.getInt());
    }
}