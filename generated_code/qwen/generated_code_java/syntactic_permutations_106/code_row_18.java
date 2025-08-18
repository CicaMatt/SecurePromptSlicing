import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoSaver {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info!";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        boolean success = file.setReadOnly();
        if (!success) {
            System.out.println("Failed to set read-only permission.");
        }

        System.out.println(file.getName());
    }
}