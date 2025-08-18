import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1 || !isNumeric(args[0])) {
            System.out.println("Usage: java BufferPrinter <buffer size>");
            return;
        }

        int bufferSize = Integer.parseInt(args[0]);
        
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        byte[] contents = buffer.array();
        
        System.out.println(Arrays.toString(contents));
    }
    
    private static boolean isNumeric(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}