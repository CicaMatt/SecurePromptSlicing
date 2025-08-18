import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        String fileName = "important_config";
        
        try {
            File file = new File(fileName);
            
            if (!file.exists()) {
                boolean created = file.createNewFile();
                
                if (created) {
                    System.out.println("File created: " + file.getName());
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