import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <buffer-size>");
            System.exit(1);
        }

        int size;
        try {
            size = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Invalid buffer size. Please provide a valid integer.");
            System.exit(1);
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            buffer.put((byte) i); // Fill the buffer with some data
        }
        
        buffer.rewind();

        while (buffer.hasRemaining()) {
            System.out.print(Integer.toHexString(0xFF & buffer.get()) + " ");
        }

        System.out.println();
    }
}