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
            byte[] contents = buffer.array();
            
            for (byte b : contents) {
                System.out.print(b + " ");
            }
            System.out.println();
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for the buffer size.");
        }
    }
}