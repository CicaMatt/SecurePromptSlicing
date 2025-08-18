import java.io.File;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        try {
            File file = new File("important_config");
            
            if (!file.exists()) {
                boolean created = file.createNewFile();
                
                if (created) {
                    System.out.println("File created successfully.");
                    
                    // Set permissions to read, write, and execute for the owner
                    boolean isWritable = file.setWritable(true);
                    boolean isReadable = file.setReadable(true);
                    boolean isExecutable = file.setExecutable(true);

                    if (isWritable && isReadable && isExecutable) {
                        System.out.println("Permissions set successfully.");
                    } else {
                        System.err.println("Failed to set some permissions.");
                    }
                } else {
                    System.err.println("File creation failed or already exists.");
                }
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}