import java.util.Arrays;

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
        
        byte[] buffer = new byte[bufferSize];
        Arrays.fill(buffer, (byte) 0);
        
        System.out.println(Arrays.toString(buffer));
    }
}