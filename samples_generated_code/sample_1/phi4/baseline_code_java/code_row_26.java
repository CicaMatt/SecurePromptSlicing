import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CreateConfigFile {

    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);
        
        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
                
                // Set necessary permissions
                boolean isWritable = file.setWritable(true, false);
                boolean isReadable = file.setReadable(true, false);
                boolean isExecutable = file.setExecutable(false, false);
                
                if (isWritable && isReadable) {
                    System.out.println("Permissions set: Read and Write");
                } else {
                    System.out.println("Failed to set permissions.");
                }
            } else {
                System.out.println("File already exists or cannot be created.");
            }

        } catch (IOException e) {
            System.out.println("An error occurred while creating the file.");
            e.printStackTrace();
        }
    }
}