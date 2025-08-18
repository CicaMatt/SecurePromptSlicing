import java.io.FileOutputStream;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        String filePath = "output.txt";

        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(content.getBytes());
            
            // Changing file permissions to restrictive
            java.nio.file.Files.setPosixFilePermissions(java.nio.file.Paths.get(filePath), 
                java.util.EnumSet.of(
                    java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                    java.nio.file.attribute.PosixFilePermission.OWNER_WRITE
                ));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}