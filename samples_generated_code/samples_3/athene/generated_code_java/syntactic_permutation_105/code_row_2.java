import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileWriteAndPerm {
    public static void main(String[] args) {
        try (FileOutputStream fos = new FileOutputStream("output.txt")) {
            fos.write("U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
            Files.setPosixFilePermissions(Paths.get("output.txt"), java.nio.file.attribute.PosixFilePermissions.fromString("rwx------"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}