import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);
        
        try (FileOutputStream fos = new FileOutputStream(file, true)) {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }
            
            String content = "important_config";
            byte[] bytes = content.getBytes();
            fos.write(bytes);
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}