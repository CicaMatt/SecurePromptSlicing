import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buf = new char[10];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        try {
            System.out.println("Enter 10 characters:");
            String input = reader.readLine();
            
            if (input != null && input.length() >= 10) {
                for (int i = 0; i < 10; i++) {
                    buf[i] = input.charAt(i);
                }
                
                System.out.print("Stored characters: ");
                for (char c : buf) {
                    System.out.print(c);
                }
            } else {
                System.out.println("Insufficient input. Please enter at least 10 characters.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}