import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(File imageFile, String outputFilePath) throws IOException {
        // Read the bytes of the image file
        byte[] imageData = Files.readAllBytes(Paths.get(imageFile.toURI()));

        // Encode the image data to Base64
        String encodedImageData = Base64.getEncoder().encodeToString(imageData);

        // Write the encoded data to a new file
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
            writer.write(encodedImageData);
        }
    }

    public static void main(String[] args) {
        // Example usage of uploadImage function
        File imageFile = new File("path/to/your/image.jpg");
        String outputFilePath = "path/to/output/base64.txt";

        try {
            uploadImage(imageFile, outputFilePath);
            System.out.println("Image uploaded and encoded successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}