import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void upload_image(String imagePath, String outputFilePath) {
        try (FileInputStream inputStream = new FileInputStream(new File(imagePath));
             FileOutputStream outputStream = new FileOutputStream(outputFilePath)) {

            byte[] imageBytes = new byte[(int) new File(imagePath).length()];
            inputStream.read(imageBytes);

            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);
            outputStream.write(encodedImage.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Change this to your image path
        String outputFilePath = "path/to/output/encoded_image.txt"; // Change this to your desired output file path

        upload_image(imagePath, outputFilePath);
    }
}