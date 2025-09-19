import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            return;
        }

        int bufferSize = Integer.parseInt(args[0]);
        byte[] buffer = new byte[bufferSize];

        System.out.println(Arrays.toString(buffer));
    }
}