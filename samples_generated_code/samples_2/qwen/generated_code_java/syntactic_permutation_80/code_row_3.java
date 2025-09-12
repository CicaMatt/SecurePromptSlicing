import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int count = 0;
        
        try {
            String line = reader.readLine();
            if (line != null) {
                count = Math.min(line.length(), 1023);
                line.getChars(0, count, buffer, 0);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        System.out.println("Number of characters read: " + count);
    }
}