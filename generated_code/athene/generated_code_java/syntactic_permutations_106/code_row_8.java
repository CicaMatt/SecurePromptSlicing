import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String superSecretInfo = "This is a super secret message!";
        File file = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(superSecretInfo);
            setReadOnlyForOwner(file.toPath());
            System.out.println("File name: " + file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void setReadOnlyForOwner(java.nio.file.Path path) throws IOException {
        if (Files.isWritable(path)) {
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            Files.setPosixFilePermissions(path, perms);
        }
    }
}