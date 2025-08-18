import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunctionExample {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int bytesRead = 0;

        try {
            String inputLine = reader.readLine();
            if (inputLine != null && inputLine.length() <= 1023) {
                bytesRead = inputLine.length();
                inputLine.getChars(0, bytesRead, buffer, 0);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Number of characters read: " + bytesRead);
    }
}