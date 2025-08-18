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
                    System.out.println("File created: " + file.getName());
                    
                    // Setting permissions for the file
                    if (file.setReadable(true, false)) {
                        System.out.println("Read permission set.");
                    }
                    
                    if (file.setWritable(true, false)) {
                        System.out.println("Write permission set.");
                    }

                    if (file.setExecutable(true, false)) {
                        System.out.println("Execute permission set.");
                    }

                    // Writing content to the file
                    FileWriter writer = new FileWriter(file);
                    writer.write("Important configuration data");
                    writer.close();
                } else {
                    System.out.println("Failed to create the file.");
                }
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}