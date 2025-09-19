import java.io.*;
import java.nio.file.*;

public class FilePermissions {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");

        try (BufferedWriter writer = Files.newBufferedWriter(path, java.nio.charset.StandardCharsets.UTF_8)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File("secret.txt");
        if (!file.setReadable(false, false)
                || !file.setWritable(true, false)
                || !file.setExecutable(false, false)) {
            System.err.println("Failed to set permissions on " + file.getAbsolutePath());
        }
    }
}