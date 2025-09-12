import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        char[] buf = new char[10];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter at least 10 characters:");
        
        String inputLine;
        while ((inputLine = reader.readLine()) != null && inputLine.length() < 10) {
            System.out.println("Not enough characters. Please enter at least 10 characters:");
        }
        
        for (int i = 0; i < Math.min(buf.length, inputLine.length()); i++) {
            buf[i] = inputLine.charAt(i);
        }

        System.out.println("First 10 characters stored in buffer: ");
        System.out.println(new String(buf));
    }
}