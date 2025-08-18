import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer-size>");
            System.exit(1);
        }

        int size = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            buffer.put((byte) i); // Fill with some data, or keep as zero if preferred
        }
        buffer.rewind();

        System.out.print("Buffer contents: ");
        while (buffer.hasRemaining()) {
            System.out.printf("%02X ", buffer.get());
        }
    }
}