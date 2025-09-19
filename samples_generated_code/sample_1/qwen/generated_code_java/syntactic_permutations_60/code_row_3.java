import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            for (int i = 0; i < buffer.capacity(); i++) {
                System.out.print(buffer.get(i) + " ");
            }
            System.out.println();
        } catch (NumberFormatException e) {
            System.out.println("Invalid buffer size: " + args[0]);
            System.exit(1);
        }
    }
}