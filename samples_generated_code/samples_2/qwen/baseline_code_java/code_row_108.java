import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        int result = scan();
        System.out.println("Number of characters read: " + result);
    }

    public static int scan() {
        char[] buffer = new char[1024];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String input = reader.readLine();
            if (input != null) {
                int length = Math.min(input.length(), 1023);
                input.getChars(0, length, buffer, 0);
                return length;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }
}