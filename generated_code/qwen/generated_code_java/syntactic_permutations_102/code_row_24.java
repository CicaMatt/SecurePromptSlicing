import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);
        
        try (FileOutputStream fos = new FileOutputStream(file, true)) {
            if (!file.exists()) {
                boolean isCreated = file.createNewFile();
                if (isCreated) {
                    file.setReadable(true, false); // S_IRUSR | S_IRGRP | S_IROTH
                    file.setWritable(true, true);  // S_IWUSR
                }
            }
            
            String contentToWrite = "important_config";
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}