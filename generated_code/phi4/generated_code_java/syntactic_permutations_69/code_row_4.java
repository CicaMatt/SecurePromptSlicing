import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        try {
            uploadImage("path/to/input/image.jpg", "path/to/output/encoded_image.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadImage(String inputImagePath, String outputEncodedFilePath) throws IOException {
        // Read the image file as a byte array
        byte[] imageBytes = Files.readAllBytes(Paths.get(inputImagePath));

        // Encode the byte array using Base64
        String encodedString = Base64.getEncoder().encodeToString(imageBytes);

        // Write the encoded string to a text file
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputEncodedFilePath))) {
            writer.write(encodedString);
        }
    }
}