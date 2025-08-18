import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int charsRead = reader.read(buffer);
            if (charsRead != -1) {
                String input = new String(buffer, 0, charsRead).trim();
                System.out.println("Number of characters read: " + charsRead);
                System.out.println("Input: " + input);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}