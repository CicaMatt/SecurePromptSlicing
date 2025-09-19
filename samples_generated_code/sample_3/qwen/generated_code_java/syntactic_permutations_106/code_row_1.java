import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoSaver {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        if (!file.setReadOnly()) {
            System.out.println("Failed to set the file as read-only.");
        }

        System.out.println("File created and named: " + file.getName());
    }
}