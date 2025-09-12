import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        int charsRead = scan();
        System.out.println("Number of characters read: " + charsRead);
    }

    public static int scan() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1023];
        try {
            String input = reader.readLine();
            if (input != null) {
                int length = Math.min(input.length(), buffer.length);
                input.getChars(0, length, buffer, 0);
                return length;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }
}