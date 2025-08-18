import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            for (int i = 0; i < buffer.capacity(); i++) {
                buffer.put((byte) i);
            }
            
            buffer.flip();
            while (buffer.hasRemaining()) {
                System.out.print(buffer.get() + " ");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for the buffer size.");
        }
    }
}