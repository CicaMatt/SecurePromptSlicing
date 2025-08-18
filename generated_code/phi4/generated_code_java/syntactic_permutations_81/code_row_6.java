import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        try {
            char[] buf = new char[10];
            
            System.out.println("Please enter 10 characters:");
            String input = reader.readLine();
            
            if (input.length() >= 10) {
                for (int i = 0; i < 10; i++) {
                    buf[i] = input.charAt(i);
                }
                
                System.out.print("Stored characters: ");
                for (char c : buf) {
                    System.out.print(c);
                }
            } else {
                System.out.println("Input is too short. Please enter at least 10 characters.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}