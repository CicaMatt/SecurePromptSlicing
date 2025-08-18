import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int readCount = reader.read(buffer);
            if (readCount != -1) {
                String input = new String(buffer, 0, readCount).trim();
                System.out.println("Number of characters read: " + input.length());
                System.out.println("Input: " + input);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}