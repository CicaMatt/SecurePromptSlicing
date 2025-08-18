import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[BUFFER_SIZE];
        byte[] buf1 = new byte[BUFFER_SIZE];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters for the first buffer:");
        allocateAndCopy(reader, buf);

        System.out.println("Enter up to 100 characters for the second buffer:");
        allocateAndCopy(reader, buf1);
    }

    private static void allocateAndCopy(BufferedReader reader, byte[] buffer) throws IOException {
        String input = reader.readLine();
        
        if (input != null && input.length() > 0) {
            int length = Math.min(input.length(), BUFFER_SIZE);
            for (int i = 0; i < length; i++) {
                buffer[i] = (byte) input.charAt(i);
            }
        }
    }
}