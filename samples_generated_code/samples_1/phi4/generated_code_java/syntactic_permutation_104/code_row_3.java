import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "config.txt";
        String dataToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            fos.write(dataToWrite.getBytes());
            System.out.println("Data written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}