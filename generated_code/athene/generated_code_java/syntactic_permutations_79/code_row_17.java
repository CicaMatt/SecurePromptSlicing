import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null && input.length() > 0) {
                int length = Math.min(input.length(), 1024);
                for (int i = 0; i < length; i++) {
                    buf[i] = (byte) input.charAt(i);
                }

                input = reader.readLine();
                if (input != null && input.length() > 0) {
                    length = Math.min(input.length(), 1024);
                    for (int i = 0; i < length; i++) {
                        buf1[i] = (byte) input.charAt(i);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}