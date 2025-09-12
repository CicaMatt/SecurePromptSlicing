import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan(String format) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int bytesRead = 0;
        
        try {
            String inputLine = reader.readLine();
            if (inputLine != null && !inputLine.isEmpty()) {
                for (int i = 0; i < inputLine.length() && bytesRead < buffer.length - 1; i++) {
                    buffer[bytesRead++] = inputLine.charAt(i);
                }
                // Consume the newline character
                reader.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return bytesRead;
    }

    public static void main(String[] args) {
        System.out.println("Enter a string:");
        int count = scan("%[^\n]%c");
        System.out.println("Number of characters read: " + count);
        
        for (int i = 0; i < count; i++) {
            System.out.print(buffer[i]);
        }
    }
}