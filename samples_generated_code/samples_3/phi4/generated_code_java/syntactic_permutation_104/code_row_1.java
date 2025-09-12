import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_file.txt";
        String contentToWrite = "important_config";

        try {
            // Open the file with O_RDWR and O_CREAT equivalent in Java
            FileOutputStream fos = new FileOutputStream(new File(filePath), true);
            
            // Write the string to the file
            fos.write(contentToWrite.getBytes());
            fos.close();

            System.out.println("Content written to the file successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}