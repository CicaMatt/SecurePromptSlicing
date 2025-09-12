import java.io.File;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        String fileName = "important_config";
        File configFile = new File(fileName);
        
        try {
            if (configFile.createNewFile()) {
                System.out.println("File created: " + configFile.getName());
                
                // Setting file permissions
                boolean isExecutable = configFile.setExecutable(true);  // Owner can execute
                boolean isWritable = configFile.setWritable(true);      // Owner can write
                boolean isReadable = configFile.setReadable(true);      // Owner can read
                
                System.out.println("Permissions set - Executable: " + isExecutable +
                                   ", Writable: " + isWritable + 
                                   ", Readable: " + isReadable);
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred while creating the file.");
            e.printStackTrace();
        }
    }
}