import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoFile {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        File file = new File("secretinfo.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        boolean isReadOnlySet = file.setReadOnly();
        if (isReadOnlySet) {
            System.out.println("File permissions changed to read-only for the owner.");
        } else {
            System.out.println("Failed to change file permissions.");
        }

        System.out.println("Name of the file: " + file.getName());
    }
}