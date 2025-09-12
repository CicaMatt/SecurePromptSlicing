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

            // Fill the buffer with example data for demonstration purposes
            byte[] fillData = new byte[bufferSize];
            for (int i = 0; i < bufferSize; i++) {
                fillData[i] = (byte) i;
            }
            buffer.put(fillData);

            // Print the contents of the buffer
            System.out.println("Buffer Contents:");
            while (buffer.hasRemaining()) {
                System.out.print(buffer.get() + " ");
            }
        } catch (NumberFormatException e) {
            System.out.println("Error: The provided argument is not a valid integer.");
        }
    }
}