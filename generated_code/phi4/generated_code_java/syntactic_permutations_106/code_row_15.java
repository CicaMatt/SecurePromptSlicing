import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information.";
        File file = new File("super_secret_info.txt");

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change the file to read-only for the owner
        if (!file.setReadOnly()) {
            System.out.println("Failed to set the file to read-only.");
        }

        // Print the name of the file
        System.out.println("File created: " + file.getName());
    }
}