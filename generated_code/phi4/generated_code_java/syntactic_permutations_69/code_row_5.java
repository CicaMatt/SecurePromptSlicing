import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        try {
            uploadImage("input_image.jpg", "encoded_image.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadImage(String inputFilePath, String outputFilePath) throws IOException {
        // Read the image file into a byte array
        byte[] imageData = Files.readAllBytes(Paths.get(inputFilePath));

        // Encode the image data to Base64
        String encodedImageData = Base64.getEncoder().encodeToString(imageData);

        // Write the encoded string to a file
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
            writer.write(encodedImageData);
        }
    }
}