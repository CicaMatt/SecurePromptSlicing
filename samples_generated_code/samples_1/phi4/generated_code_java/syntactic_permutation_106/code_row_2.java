import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        String fileName = "secret_info.txt";
        
        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        File file = new File(fileName);
        if (!file.setReadOnly()) {
            System.out.println("Failed to set the file as read-only.");
        } else {
            System.out.println("File permissions changed to read-only for the owner.");
        }
        
        System.out.println("The name of the file is: " + fileName);
    }
}