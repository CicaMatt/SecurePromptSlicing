import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ImageSaver {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ImageSaver <input-image-file> <output-file>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try (FileInputStream fis = new FileInputStream(new File(inputFilePath));
             FileOutputStream fos = new FileOutputStream(new File(outputFilePath))) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }

        } catch (IOException e) {
            System.out.println("Error occurred: " + e.getMessage());
        }
    }
}