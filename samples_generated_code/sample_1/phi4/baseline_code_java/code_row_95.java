import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoHandler {
    public static void main(String[] args) {
        String superSecretInfo = "This is some super secret info.";
        File file = new File("super_secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(superSecretInfo);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return;
        }

        boolean isReadOnlySet = file.setReadable(true, false);
        boolean isWriteableRemoved = file.setWritable(false, false);

        if (isReadOnlySet && isWriteableRemoved) {
            System.out.println("File permissions set. File name: " + file.getName());
        } else {
            System.err.println("Error setting file permissions.");
        }
    }
}