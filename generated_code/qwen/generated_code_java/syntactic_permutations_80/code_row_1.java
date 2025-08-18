import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunctionExample {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int length = reader.read(buffer, 0, 1023);
            String inputString = new String(buffer, 0, length).trim();
            System.out.println("Number of characters read: " + length);
            System.out.println("Read string: " + inputString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}