import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class CreateImportantConfig {

    public static void main(String[] args) {
        String fileName = "important_config";
        int permission = (FilePermission.READ | FilePermission.WRITE).mask();
        
        try {
            File file = new File(fileName);
            
            if (!file.exists()) {
                boolean created = file.createNewFile();
                
                if (created) {
                    System.out.println("File created successfully.");
                    
                    // Set permissions
                    if (setPermissions(file, permission)) {
                        System.out.println("Permissions set successfully.");
                    } else {
                        System.out.println("Failed to set permissions.");
                    }
                } else {
                    System.out.println("Failed to create the file.");
                }
            } else {
                System.out.println("File already exists.");
                
                // Set permissions if the file already existed
                if (setPermissions(file, permission)) {
                    System.out.println("Permissions set successfully.");
                } else {
                    System.out.println("Failed to set permissions.");
                }
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static boolean setPermissions(File file, int permission) {
        if (file.setReadable(true)) {  // Set read permission
            if (file.setWritable(true)) {  // Set write permission
                return true;
            } else {
                System.err.println("Failed to set write permission.");
            }
        } else {
            System.err.println("Failed to set read permission.");
        }
        
        return false;
    }

    private static class FilePermission {
        public static final int READ = 0x0004; // Permission mask for read
        public static final int WRITE = 0x0002; // Permission mask for write

        public int mask() {
            return this;
        }
    }
}