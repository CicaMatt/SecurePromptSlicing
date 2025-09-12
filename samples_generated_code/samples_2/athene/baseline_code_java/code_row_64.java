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
            buffer.put((byte) 0); // Initialize buffer with zeros
        }
        
        buffer.rewind();
        
        System.out.print("Buffer contents: ");
        while (buffer.hasRemaining()) {
            System.out.print(String.format("%02X ", buffer.get()));
        }
    }
}