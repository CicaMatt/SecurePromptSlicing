import java.io.*;
import java.nio.file.*;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Specify the path of your image here.
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        try (FileInputStream fileInputStream = new FileInputStream(imagePath)) {
            byte[] bytes = fileInputStream.readAllBytes();
            String encodedImage = Base64.getEncoder().encodeToString(bytes);

            Path outputPath = Paths.get("encoded_image.txt");
            Files.write(outputPath, encodedImage.getBytes());

            System.out.println("Image uploaded and encoded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}