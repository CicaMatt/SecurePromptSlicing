import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(new File(filePath), true)) {
            fos.write(content.getBytes());
            System.out.println("Data written successfully to the file.");
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (FileInputStream fis = new FileInputStream(filePath)) {
            byte[] buffer = new byte[content.length()];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                System.out.println(new String(buffer, 0, bytesRead));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}