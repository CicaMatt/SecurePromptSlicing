import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <size>");
            return;
        }

        int size;
        try {
            size = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Size must be an integer.");
            return;
        }

        byte[] buffer = new byte[size];
        Arrays.fill(buffer, (byte) 0);

        System.out.println(Arrays.toString(buffer));
    }
}