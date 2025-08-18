import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SuperSecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        String fileName = "super_secret_info.txt";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);

        // Change the file permissions to read-only for the owner
        if (file.setReadable(true, false) && file.setWritable(false, false)) {
            System.out.println("File permissions changed successfully.");
        } else {
            System.err.println("Failed to change file permissions.");
        }

        // Print the name of the file
        System.out.println("The file is: " + fileName);
    }
}