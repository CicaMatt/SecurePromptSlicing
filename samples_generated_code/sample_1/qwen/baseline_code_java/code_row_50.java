import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <size>");
            return;
        }

        int size;
        try {
            size = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Invalid buffer size specified.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(size);

        for (int i = 0; i < buffer.capacity(); i++) {
            System.out.print(buffer.get(i));
        }
    }
}