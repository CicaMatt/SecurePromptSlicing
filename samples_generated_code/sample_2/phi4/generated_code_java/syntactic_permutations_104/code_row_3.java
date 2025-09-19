import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String contentToWrite = "This is an important configuration file.";

        try {
            FileOutputStream fos = new FileOutputStream(new File(fileName), true);
            fos.write(contentToWrite.getBytes());
            fos.close();
            System.out.println("File written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}