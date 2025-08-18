import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <buffer-size>");
            System.exit(1);
        }
        
        int size = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(size);
        
        for (int i = 0; i < size; i++) {
            buffer.put((byte) i); // Fill the buffer with some data
        }
        
        buffer.rewind(); // Reset position to start of buffer
        
        System.out.print("Buffer contents: ");
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
        
        System.exit(0);
    }
}