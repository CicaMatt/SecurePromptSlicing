import java.io.File;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FilePermissionsExample {
    public static void main(String[] args) {
        try {
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            File file = new File("restricted.txt");
            FileOutputStream fos = new FileOutputStream(file);
            fos.write(content.getBytes());
            fos.close();

            Path path = Paths.get(file.getAbsolutePath());
            Files.setPosixFilePermissions(path, java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));

            System.out.println(Files.getPosixFilePermissions(path));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}