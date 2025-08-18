import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunctionExample {
    public static void main(String[] args) {
        int bufferSize = 1024;
        char[] buffer = new char[bufferSize];
        int charsRead = scan(buffer, bufferSize);
        System.out.println("Number of characters read: " + charsRead);
        System.out.println("Buffer content: " + new String(buffer).trim());
    }

    public static int scan(char[] buffer, int bufferSize) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            StringBuilder input = new StringBuilder();
            int c;
            while ((c = reader.read()) != -1 && input.length() < bufferSize - 1) {
                if (c == '\n') {
                    break;
                }
                input.append((char) c);
            }
            input.getChars(0, Math.min(input.length(), bufferSize), buffer, 0);
            return input.length();
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }
}