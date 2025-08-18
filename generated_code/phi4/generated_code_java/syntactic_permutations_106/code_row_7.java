import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoFile {

    public static void main(String[] args) {
        String secretInfo = "super secret info";
        File file = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("Error writing to the file: " + e.getMessage());
            return;
        }

        if (!file.setReadOnly()) {
            System.err.println("Failed to set the file as read-only.");
        } else {
            System.out.println("The file has been created and is read-only for the owner: " + file.getName());
        }
    }
}