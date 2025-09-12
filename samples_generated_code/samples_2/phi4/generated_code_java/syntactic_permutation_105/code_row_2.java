import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileCreator {

    public static void main(String[] args) {
        String fileName = "output.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        Path path = Paths.get(fileName);
        java.nio.file.attribute.PosixFilePermissions permissions = 
                java.nio.file.attribute.PosixFilePermissions.fromString("rw-------");
        
        try {
            Files.setPosixFilePermissions(path, permissions);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}