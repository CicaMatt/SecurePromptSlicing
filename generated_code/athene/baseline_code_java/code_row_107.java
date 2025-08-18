import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        File file = new File("secret.txt");

        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(content.getBytes());
            fos.flush();

            if (file.setWritable(false, false) && file.setReadable(false, false) && file.setExecutable(false, false)) {
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);

                java.nio.file.Files.setPosixFilePermissions(file.toPath(), perms);
            }

            System.out.println(java.nio.file.Files.getPosixFilePermissions(file.toPath()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}