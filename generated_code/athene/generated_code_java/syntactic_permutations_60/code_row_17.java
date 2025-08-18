import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: BufferAllocator <size>");
            return;
        }
        int size = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(size);
        System.out.print(".");
    }
}