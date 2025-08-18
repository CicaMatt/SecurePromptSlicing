import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret info that should not be shared.";
        File file = new File("superSecretFile.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        // Changing permissions is not directly supported in Java's standard API.
        // This part of the code would require using system-specific commands or a third-party library.
        // Below is an example for Unix-based systems (Linux, macOS) to change permissions:
        try {
            Process process = Runtime.getRuntime().exec("chmod 600 " + file.getAbsolutePath());
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.out.println("Failed to change file permissions.");
            }
        } catch (IOException | InterruptedException e) {
            System.out.println("An error occurred while changing the file permissions.");
            e.printStackTrace();
        }

        System.out.println("File created: " + file.getName());
    }
}