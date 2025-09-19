import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buf = new char[10];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.println("Please enter 10 characters:");
            String input = reader.readLine();
            
            if (input != null && input.length() >= 10) {
                for (int i = 0; i < 10; i++) {
                    buf[i] = input.charAt(i);
                }
                
                System.out.println("Buffer contents: " + new String(buf));
            } else {
                System.err.println("Not enough characters entered.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}