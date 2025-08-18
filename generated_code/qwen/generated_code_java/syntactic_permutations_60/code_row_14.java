import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            return;
        }
        
        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Buffer size must be an integer.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        for (int i = 0; i < buffer.capacity(); i++) {
            System.out.print(buffer.get(i) + " ");
        }
    }
}