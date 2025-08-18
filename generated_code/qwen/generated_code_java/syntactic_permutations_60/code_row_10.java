import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.exit(1);
        }
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        byte[] array = buffer.array();
        for (byte b : array) {
            System.out.print(b + " ");
        }
        System.out.println();
    }
}