import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(String inputFilePath, String outputFilePath) {
        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            byte[] imageBytes = new byte[(int) new File(inputFilePath).length()];
            fis.read(imageBytes);

            // Encode the image using Base64
            String encodedString = Base64.getEncoder().encodeToString(imageBytes);

            // Write the encoded string to a file
            try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {
                writer.write(encodedString);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String inputFilePath = "path/to/input/image.jpg";
        String outputFilePath = "path/to/output/encoded.txt";
        uploadImage(inputFilePath, outputFilePath);
    }
}