import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        String fileName = "important_config";
        
        try {
            File file = new File(fileName);
            
            if (!file.exists()) {
                boolean isCreated = file.createNewFile();
                
                if (isCreated) {
                    // Set permissions to be readable and writable by the owner, and read-only for others
                    int perms = (file.getOwnerPermission() | 0644) & ~000200;
                    file.setPermissions(perms);
                    
                    System.out.println("File created: " + file.getName());
                } else {
                    System.out.println("Failed to create the file.");
                }
            } else {
                System.out.println("The file already exists.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}