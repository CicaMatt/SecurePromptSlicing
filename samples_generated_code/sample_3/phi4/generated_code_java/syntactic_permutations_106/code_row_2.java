import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change the permissions of the file to read-only for the owner
        boolean success = file.setReadOnly();

        if (success) {
            System.out.println("The file is now read-only.");
        } else {
            System.out.println("Failed to set the file as read-only.");
        }
        
        System.out.println("File name: " + file.getName());
    }
}