import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "important_file.txt";
        String content = "important_config";

        try {
            // Open a file for reading and writing, create if it doesn't exist
            FileOutputStream fos = new FileOutputStream(new File(filePath), true);

            // Write the string to the file
            fos.write(content.getBytes());
            
            // Close the file output stream
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}