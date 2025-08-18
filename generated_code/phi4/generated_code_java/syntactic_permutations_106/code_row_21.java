import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoHandler {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("super_secret_info.txt");

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        // Change permissions: owner can read and write, others have no permissions
        boolean success = file.setReadable(true, true);
        success &= file.setWritable(true, true);
        success &= file.setExecutable(false, false);

        if (!success) {
            System.out.println("Failed to set file permissions.");
        } else {
            System.out.println("File created and permissions set: " + file.getName());
        }
    }
}