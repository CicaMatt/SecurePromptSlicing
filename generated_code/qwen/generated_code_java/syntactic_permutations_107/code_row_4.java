import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermissions;

public class FilePermissionExample {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        File file = new File("output.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(content);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        try {
            Files.setPosixFilePermissions(file.toPath(), PosixFilePermissions.fromString("r--------"));
            System.out.println("File permissions set to: " + Files.getPosixFilePermissions(file.toPath()));
        } catch (IOException e) {
            System.out.println("An error occurred while changing file permissions.");
            e.printStackTrace();
        }
    }
}