import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) throws IOException {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(content.getBytes());
        }

        // Change file permissions to be read-only
        if (new java.io.File(fileName).setReadable(true, false) &&
            new java.io.File(fileName).setWritable(false, false) &&
            new java.io.File(fileName).setExecutable(false, false)) {
            System.out.println("Permissions changed successfully.");
        } else {
            System.out.println("Failed to change permissions.");
        }
    }
}