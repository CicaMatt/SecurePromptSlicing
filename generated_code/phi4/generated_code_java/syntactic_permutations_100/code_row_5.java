import java.io.File;
import java.io.IOException;

public class CreateFileWithPermissions {
    public static void main(String[] args) {
        String fileName = "important_config";
        
        try {
            // Set the permissions (read, write, and execute for owner; read and execute for group and others)
            int permissions = (S_IRUSR | S_IWUSR | S_IXUSR) |
                              (S_IRGRP | S_IXGRP) |
                              (S_IROTH | S_IXOTH);
            
            File file = new File(fileName);
            
            boolean created = file.createNewFile();
            if (created) {
                System.out.println("File " + fileName + " has been created.");
                
                // Set the permissions
                if (file.setReadable(true, false)) {
                    System.out.println("Read permission set for owner.");
                }
                if (file.setWritable(true, false)) {
                    System.out.println("Write permission set for owner.");
                }
                if (file.setExecutable(true, false)) {
                    System.out.println("Execute permission set for owner.");
                }
                
                // Setting permissions for group and others
                boolean isGroupAndOthersSet = file.setReadable(true, true) &&
                                              file.setWritable(false, true) && // No write permission for group and others
                                              file.setExecutable(true, true);
                if (isGroupAndOthersSet) {
                    System.out.println("Read and execute permissions set for group and others.");
                }
                
            } else {
                System.out.println("File " + fileName + " already exists.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // File permission constants
    private static final int S_IRUSR = 0400;
    private static final int S_IWUSR = 0200;
    private static final int S_IXUSR = 0100;

    private static final int S_IRGRP = 0040;
    private static final int S_IWGRP = 0020;
    private static final int S_IXGRP = 0010;

    private static final int S_IROTH = 0004;
    private static final int S_IWOTH = 0002;
    private static final int S_IXOTH = 0001;
}