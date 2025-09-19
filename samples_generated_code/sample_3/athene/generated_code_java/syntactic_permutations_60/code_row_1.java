import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer-size>");
            return;
        }
        
        int size = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(size);
        
        for (int i = 0; i < size; i++) {
            buffer.put((byte) i); // Fill with some data
        }
        
        buffer.rewind();
        
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
    }
}