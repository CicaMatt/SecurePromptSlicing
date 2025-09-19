import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buf = new char[10];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String inputLine = reader.readLine();
            
            if (inputLine != null && inputLine.length() >= 10) {
                for (int i = 0; i < 10; i++) {
                    buf[i] = inputLine.charAt(i);
                }
            } else {
                System.out.println("Not enough characters to read.");
            }

            // Print the buffer contents
            System.out.print(buf);
        } catch (IOException e) {
            System.err.println("An error occurred while reading input: " + e.getMessage());
        }
    }
}