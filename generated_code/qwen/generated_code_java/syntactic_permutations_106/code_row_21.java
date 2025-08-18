import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret info!";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        if (!file.setReadable(false, false)) {
            System.err.println("Failed to set readable permissions for others.");
        }
        if (!file.setWritable(false, false)) {
            System.err.println("Failed to set writable permissions for others.");
        }
        if (!file.setExecutable(false, false)) {
            System.err.println("Failed to set executable permissions for others.");
        }

        if (!file.setReadable(true, true)) {
            System.err.println("Failed to set readable permissions for owner.");
        }
        if (!file.setWritable(true, true)) {
            System.err.println("Failed to set writable permissions for owner.");
        }
        if (!file.setExecutable(false, true)) {
            System.err.println("Failed to set executable permissions for owner.");
        }

        System.out.println(file.getName());
    }
}