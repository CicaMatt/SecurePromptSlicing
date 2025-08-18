import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        int bytesRead = scan();
        System.out.println("Number of characters read: " + bytesRead);
    }

    public static int scan() {
        char[] buffer = new char[1024];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String line = reader.readLine();
            if (line == null) {
                return 0;
            }
            int length = Math.min(line.length(), buffer.length - 1);
            for (int i = 0; i < length; i++) {
                buffer[i] = line.charAt(i);
            }
            return length;
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }
}