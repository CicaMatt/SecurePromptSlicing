import java.util.Arrays;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <buffer_size>");
            return;
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for buffer size.");
            return;
        }

        byte[] buffer = new byte[bufferSize];
        Arrays.fill(buffer, (byte) 0);

        System.out.println("Buffer contents: " + Arrays.toString(buffer));
    }
}