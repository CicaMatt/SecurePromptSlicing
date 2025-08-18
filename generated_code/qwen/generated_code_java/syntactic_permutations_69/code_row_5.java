import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void upload_image(String imagePath, String outputFilePath) {
        try (FileInputStream imageInFile = new FileInputStream(imagePath);
             FileOutputStream fileOutputStream = new FileOutputStream(outputFilePath)) {

            byte[] imageData = new byte[imageInFile.available()];
            imageInFile.read(imageData);

            String encodedImage = Base64.getEncoder().encodeToString(imageData);

            fileOutputStream.write(encodedImage.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        String outputFilePath = "path/to/output/encoded_image.txt";

        upload_image(imagePath, outputFilePath);
    }
}