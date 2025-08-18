import java.io.*;

public class MemoryAllocation {

    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String inputLine = reader.readLine();
            
            if (inputLine != null && inputLine.length() >= 10) {
                System.arraycopy(inputLine.getBytes(), 0, buf, 0, 10);
            } else {
                System.out.println("Input must be at least 10 characters long.");
            }

            System.out.write(buf, 0, 10);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}