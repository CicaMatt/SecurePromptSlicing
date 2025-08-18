import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <size>");
            return;
        }

        int size = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(size);

        for (int i = 0; i < buffer.capacity(); i++) {
            System.out.print(buffer.get(i));
        }
    }
}