import java.io.File;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);

        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
                
                // Set necessary permissions
                file.setReadable(true, false);
                file.setWritable(true, false);
                file.setExecutable(false, false);  // No execution rights

                // Setting Unix/Linux specific permissions
                if (file.exists()) {
                    int perms = file.getCanonicalFile().getOwnerPermissions();
                    perms |= java.nio.file.attribute.PosixFilePermissions.ARGV0;
                    perms &= ~java.nio.file.attribute.PosixFilePermissions.GROUP_READ;
                    perms &= ~java.nio.file.attribute.PosixFilePermissions.GROUP_WRITE;
                    perms &= ~java.nio.file.attribute.PosixFilePermissions.OTHERS_EXECUTE;

                    java.nio.file.Files.setPosixFilePermissions(file.toPath(), 
                        java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
                }
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}