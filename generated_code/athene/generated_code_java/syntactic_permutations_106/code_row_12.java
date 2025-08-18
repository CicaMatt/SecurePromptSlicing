import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        try {
            File file = new File("secret.txt");
            FileWriter writer = new FileWriter(file);
            writer.write(secretInfo);
            writer.close();
            
            Path path = Paths.get(file.getAbsolutePath());
            Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("r--------"));
            
            System.out.println(file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}