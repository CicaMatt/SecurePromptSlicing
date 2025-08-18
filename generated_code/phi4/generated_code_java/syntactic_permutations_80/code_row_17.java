import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder buffer = new StringBuilder(1024);
        
        String line;
        while ((line = reader.readLine()) != null) {
            if (buffer.length() + line.length() < 1023) {
                buffer.append(line).append("\n");
            } else {
                break;
            }
        }

        int charactersRead = buffer.toString().length();
        return charactersRead - 1; // Subtract one to exclude the last newline character
    }

    public static void main(String[] args) throws IOException {
        int numberOfCharacters = scan();
        System.out.println("Number of characters read (excluding newline): " + numberOfCharacters);
    }
}