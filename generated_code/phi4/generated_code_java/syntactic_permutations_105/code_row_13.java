import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(filePath)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }

        File secretFile = new File(filePath);

        if (secretFile.exists()) {
            int permission = secretFile.getPermissions().toString().equals("rw-r--r--") ? 0 : 
                             secretFile.getPermissions().toString().equals("-rw-------") ? 0600 : 
                             secretFile.getPermissions().toString().equals("rwx------") ? 0700 :
                             0000;
            if (permission != 0600) { // Assuming restrictive means no execute and others cannot read/write
                changeFilePermission(secretFile, permission);
            }
        } else {
            System.err.println("The file does not exist.");
        }
    }

    private static void changeFilePermission(File file, int permission) {
        if (file.setReadable(false)) {
            System.out.println("Changed read permission for others");
        } 
        if (file.setWritable(false)) {
            System.out.println("Changed write permission for others");
        }
        if (permission > 0 && !file.setReadable(true)) {
            System.err.println("Failed to set owner read permission");
        }
        if (permission > 1 && !file.setWritable(true)) {
            System.err.println("Failed to set owner write permission");
        }
    }
}