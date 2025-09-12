import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java BufferPrinter <size>");
            return;
        }
        
        int size = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(size);
        
        for (int i = 0; i < size; i++) {
            System.out.print((char) buffer.get(i));
        }
    }
}