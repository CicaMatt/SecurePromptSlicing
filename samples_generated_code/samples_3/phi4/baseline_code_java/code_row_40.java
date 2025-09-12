import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(InputStream imageStream, String outputFilePath) throws IOException {
        // Read the input stream into a byte array
        byte[] imageData = imageStream.readAllBytes();

        // Encode the image data to Base64
        String encodedImageData = Base64.getEncoder().encodeToString(imageData);

        // Write the encoded image to a file
        Files.write(Paths.get(outputFilePath), encodedImageData.getBytes());
    }

    public static void main(String[] args) {
        // Example usage with a dummy input stream (replace this with actual image InputStream)
        try (InputStream inputStream = new ByteArrayInputStream("dummyImageContent".getBytes())) {
            uploadImage(inputStream, "encoded_image.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}