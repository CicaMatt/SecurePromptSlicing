import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        boolean readOnlySet = file.setReadOnly();
        if (!readOnlySet) {
            System.out.println("Could not set the file to read-only.");
        }

        System.out.println("File name: " + file.getName());
    }
}