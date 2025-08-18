import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "example.txt";
        Path path = Paths.get(filePath);
        try {
            if (Files.notExists(path)) {
                Files.createFile(path);
                Files.setPosixFilePermissions(path, 
                    java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"));
                System.out.println("File created with permissions set.");
            } else {
                System.out.println("File already exists.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}