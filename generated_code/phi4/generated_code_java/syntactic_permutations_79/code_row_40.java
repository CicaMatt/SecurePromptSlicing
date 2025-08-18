import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf1 = new byte[1024];
        byte[] buf2 = new byte[1024];

        System.out.println("Enter up to 100 characters for the first buffer:");
        readFromStdin(reader, buf1);

        System.out.println("Enter up to 100 characters for the second buffer:");
        readFromStdin(reader, buf2);
    }

    private static void readFromStdin(BufferedReader reader, byte[] buffer) throws IOException {
        String input = reader.readLine();
        if (input != null && input.length() > 0) {
            int length = Math.min(input.length(), 100);
            for (int i = 0; i < length; i++) {
                buffer[i] = (byte) input.charAt(i);
            }
        }
    }
}