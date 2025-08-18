import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileReadWrite {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String contentToWrite = ".";
        
        try {
            File file = new File(filePath);
            FileOutputStream fos = new FileOutputStream(file, true); // O_CREAT and O_RDWR flags equivalent in Java
            
            fos.write(contentToWrite.getBytes());
            fos.close();
            
            System.out.println("File written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}