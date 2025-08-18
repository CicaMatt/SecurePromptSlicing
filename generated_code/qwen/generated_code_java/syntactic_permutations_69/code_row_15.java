import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Base64;

public class ImageUploader {

    public static void upload_image(String imagePath, String outputFilePath) throws IOException {
        byte[] imageBytes = Files.readAllBytes(new File(imagePath).toPath());
        String base64EncodedImage = Base64.getEncoder().encodeToString(imageBytes);

        try (FileOutputStream fileOutputStream = new FileOutputStream(outputFilePath)) {
            fileOutputStream.write(base64EncodedImage.getBytes());
        }
    }

    public static void main(String[] args) {
        try {
            upload_image("path/to/your/image.jpg", "path/to/output/base64image.txt");
            System.out.println("Image uploaded and encoded successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}