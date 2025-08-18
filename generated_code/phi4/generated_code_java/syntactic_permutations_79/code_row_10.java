import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws Exception {
        // Allocate first buffer of 1024 bytes
        byte[] buf = new byte[1024];
        
        // Copy up to 100 characters into the first buffer from standard input
        copyInputToBuffer(buf, 100);

        // Allocate second buffer of 1024 bytes
        byte[] buf1 = new byte[1024];

        // Copy up to 100 characters into the second buffer from standard input
        copyInputToBuffer(buf1, 100);
    }

    private static void copyInputToBuffer(byte[] buffer, int maxChars) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter up to " + maxChars + " characters:");
        
        String input = reader.readLine();
        if (input != null && input.length() > 0) {
            // Copy the input to the buffer, limited by the smaller of input length or buffer size
            int lengthToCopy = Math.min(input.length(), buffer.length);
            for (int i = 0; i < lengthToCopy; i++) {
                buffer[i] = (byte) input.charAt(i);
            }
        }

        // Print out the content copied to verify
        System.out.println("Buffer Content: " + new String(buffer).trim());
    }
}