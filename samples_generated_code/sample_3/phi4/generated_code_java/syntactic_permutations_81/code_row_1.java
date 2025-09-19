import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        char[] buffer = new char[10];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.println("Enter 10 characters:");
            String input = reader.readLine();
            
            if (input.length() >= 10) {
                for (int i = 0; i < 10; i++) {
                    buffer[i] = input.charAt(i);
                }
                System.out.println("Characters stored in buffer: ");
                for (char c : buffer) {
                    System.out.print(c + " ");
                }
            } else {
                System.out.println("Not enough characters entered.");
            }
        }
    }
}