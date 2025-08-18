import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

public class ImportantConfig {

    public static void main(String[] args) {
        try {
            File file = new File("important_config");
            boolean fileCreated = file.createNewFile();
            
            if (fileCreated || file.exists()) {
                String content = "important_config";
                
                try (FileOutputStream fos = new FileOutputStream(file, true);
                     OutputStreamWriter writer = new OutputStreamWriter(fos)) {
                    
                    writer.write(content);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}