import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String fileName = "secret.txt";
        String secretContent = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretContent);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        File secretFile = new File(fileName);

        // Changing permissions to restrictive, owner can read and write only
        if (!secretFile.setReadable(true, false)) {  // Owner readable
            System.err.println("Failed to set readable permission for owner.");
        }
        if (!secretFile.setWritable(true, false)) {  // Owner writable
            System.err.println("Failed to set writable permission for owner.");
        }

        // Making the file not accessible by group and others
        secretFile.setReadable(false, true);  // Not readable by group
        secretFile.setWritable(false, true);  // Not writable by group
        secretFile.setExecutable(false, true); // Not executable by group

        secretFile.setReadable(false, false); // Not readable by others
        secretFile.setWritable(false, false); // Not writable by others
        secretFile.setExecutable(false, false); // Not executable by others

        // Print permissions using Java's File class (not all platforms support this)
        System.out.println("Permissions: " + getFilePermissions(secretFile));
    }

    private static String getFilePermissions(File file) {
        if (!file.exists()) {
            return "File does not exist";
        }
        
        int permissions = file.get Permissions();
        StringBuilder sb = new StringBuilder();

        // Readable by owner
        if ((permissions & 0x0001) == 0x0001) {
            sb.append("r");
        } else {
            sb.append("-");
        }

        // Writable by owner
        if ((permissions & 0x0002) == 0x0002) {
            sb.append("w");
        } else {
            sb.append("-");
        }

        // Executable by owner
        if ((permissions & 0x0004) == 0x0004) {
            sb.append("x");
        } else {
            sb.append("-");
        }

        // Readable by group
        if ((permissions & 0x0010) == 0x0010) {
            sb.append("r");
        } else {
            sb.append("-");
        }

        // Writable by group
        if ((permissions & 0x0020) == 0x0020) {
            sb.append("w");
        } else {
            sb.append("-");
        }

        // Executable by group
        if ((permissions & 0x0040) == 0x0040) {
            sb.append("x");
        } else {
            sb.append("-");
        }

        // Readable by others
        if ((permissions & 0x0100) == 0x0100) {
            sb.append("r");
        } else {
            sb.append("-");
        }

        // Writable by others
        if ((permissions & 0x0200) == 0x0200) {
            sb.append("w");
        } else {
            sb.append("-");
        }

        // Executable by others
        if ((permissions & 0x0400) == 0x0400) {
            sb.append("x");
        } else {
            sb.append("-");
        }

        return sb.toString();
    }
}