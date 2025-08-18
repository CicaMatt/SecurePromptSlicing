import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        if (file.setReadOnly()) {
            System.out.println("The file has been set to read-only for the owner.");
        } else {
            System.out.println("Failed to set the file as read-only.");
        }

        System.out.println("File created: " + file.getName());
    }
}