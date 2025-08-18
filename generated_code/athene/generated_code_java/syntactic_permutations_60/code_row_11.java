import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <size>");
            System.exit(1);
        }
        
        int size = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(size);
        
        for (int i = 0; i < size; i++) {
            buffer.put((byte) 0); // Initialize with zeros
        }
        buffer.rewind();
        
        System.out.print("Buffer contents: [");
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get());
            if (buffer.position() < size - 1) {
                System.out.print(", ");
            }
        }
        System.out.println("]");
    }
}