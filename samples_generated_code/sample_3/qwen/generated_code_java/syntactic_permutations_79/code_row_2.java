import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input = reader.readLine();

        if (input.length() > 1024) {
            input = input.substring(0, 1024);
        }

        for (int i = 0; i < input.length(); i++) {
            buf[i] = (byte) input.charAt(i);
            if (i < 100) {
                buf1[i] = (byte) input.charAt(i);
            }
        }
    }
}