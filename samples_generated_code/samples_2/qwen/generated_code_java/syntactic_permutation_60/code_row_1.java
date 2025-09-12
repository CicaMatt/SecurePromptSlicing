import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            
            for (int i = 0; i < bufferSize; i++) {
                System.out.print(buffer.get(i));
            }
        } catch (NumberFormatException e) {
            System.exit(1);
        }
    }
}