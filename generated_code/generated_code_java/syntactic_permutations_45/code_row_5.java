import java.io.*;

public class SafeFileReader {
    public static void main(String[] args) {
        String fileName = "myFile.txt";
        String filePath = "/safe/path/to/" + fileName;
        
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + fileName);
        }
    }
}