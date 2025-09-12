import java.nio.file.*;
import java.util.Base64;
import java.io.*;

public class ImageUploader {

    public void upload_image(Path imagePath) {
        try {
            byte[] imageData = Files.readAllBytes(imagePath);
            String encodedImage = Base64.getEncoder().encodeToString(imageData);
            Path outputFilePath = Paths.get("encoded_image.txt");
            Files.write(outputFilePath, encodedImage.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image(Paths.get(args[0]));
    }
}