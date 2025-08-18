import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        String secretText = "This is some super secret info.";
        File file = new File("secret_info.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretText);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
        
        if (file.setReadable(true, false) && file.setWritable(false, false) && file.setExecutable(true, false)) {
            System.out.println("File permissions set successfully.");
        }

        System.out.println("File name: " + file.getName());
    }
}