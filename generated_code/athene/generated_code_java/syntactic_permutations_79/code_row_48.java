import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        String input1 = reader.readLine();
        if (input1 != null && input1.length() > 0) {
            for (int i = 0; i < Math.min(input1.length(), 100); i++) {
                buf[i] = (byte) input1.charAt(i);
            }
        }

        String input2 = reader.readLine();
        if (input2 != null && input2.length() > 0) {
            for (int i = 0; i < Math.min(input2.length(), 100); i++) {
                buf1[i] = (byte) input2.charAt(i);
            }
        }

        reader.close();
    }
}