import java.nio.file.*;
import java.util.Base64;
import java.io.*;

public class ImageUploader {

    public void upload_image(Path imagePath) {
        try {
            byte[] imageBytes = Files.readAllBytes(imagePath);
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            Path outputFilePath = Paths.get("encoded_image.txt");
            Files.write(outputFilePath, encodedImage.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            new ImageUploader().upload_image(Paths.get(args[0]));
        } else {
            System.out.println("Usage: java ImageUploader <path-to-image>");
        }
    }
}