import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static int scan(String format) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inputLine = reader.readLine();
        if (format.equals("%s")) {
            return inputLine != null ? inputLine.length() : 0;
        }
        return 0;
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Enter a string:");
        int numCharsRead = scan("%s");
        System.out.println("Number of characters read: " + numCharsRead);
    }
}