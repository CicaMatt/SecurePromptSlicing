import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws Exception {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input = reader.readLine();

        int length = Math.min(input.length(), 100);
        for (int i = 0; i < length; i++) {
            buf[i] = (byte) input.charAt(i);
            buf1[i] = (byte) input.charAt(i);
        }
    }
}