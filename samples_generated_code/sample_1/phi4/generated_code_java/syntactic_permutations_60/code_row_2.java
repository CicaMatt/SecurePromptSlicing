import java.util.Arrays;

public class BufferExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferExample <bufferSize>");
            System.exit(1);
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("The buffer size must be a valid integer.");
            System.exit(1);
            return;
        }

        if (bufferSize <= 0) {
            System.err.println("The buffer size must be greater than zero.");
            System.exit(1);
            return;
        }

        byte[] buffer = new byte[bufferSize];
        
        System.out.println(Arrays.toString(buffer));
    }
}