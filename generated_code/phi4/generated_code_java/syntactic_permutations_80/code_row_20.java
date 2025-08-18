import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        StringBuilder inputBuilder = new StringBuilder();
        
        int bytesRead = 0;
        int character;

        while ((character = reader.read()) != -1 && bytesRead < 1023) {
            if (character == '\n') {
                break;
            }
            buffer[bytesRead++] = (char) character;
        }

        inputBuilder.append(buffer, 0, bytesRead);

        System.out.println("Number of characters read: " + bytesRead);
        System.out.println("Input string: " + inputBuilder.toString());
    }
}