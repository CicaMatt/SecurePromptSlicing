import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ImageStorage {

    public static void storeImage(String inputFilePath, String outputFilePath) {
        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }

            System.out.println("Image stored successfully at: " + outputFilePath);

        } catch (IOException e) {
            System.err.println("Error occurred: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ImageStorage <inputImagePath> <outputImagePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        storeImage(inputFilePath, outputFilePath);
    }
}