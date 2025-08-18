import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Print the contents of the buffer
            for (int i = 0; i < buffer.capacity(); i++) {
                System.out.print(buffer.get(i) + " ");
            }
            System.out.println();
        } catch (NumberFormatException e) {
            System.out.println("Error: Please provide a valid integer as buffer size.");
        }
    }
}