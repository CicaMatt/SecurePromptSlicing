import java.io.File;
import java.nio.file.*;

public class SecretInfo {
    public static void main(String[] args) throws Exception {
        String secret = "I am a string with some super secret info";

        File file = new File("superSecret.txt");

        Files.write(Paths.get("superSecret.txt"), secret.getBytes());

        if (file.setWritable(false)) {
            System.out.println("File permission changed to read-only.");
        } else {
            System.out.println("Failed to change the file permission.");
        }
    }
}