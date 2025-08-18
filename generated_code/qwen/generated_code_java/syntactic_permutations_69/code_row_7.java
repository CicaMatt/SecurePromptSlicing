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

            String base64Image = Base64.getEncoder().encodeToString(imageData);
            byte[] strToBytes = base64Image.getBytes();

            fileOutputStream.write(strToBytes);

        } catch (IOException e) {
            System.out.println("Exception while reading the Image " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        upload_image("path/to/your/image.jpg", "path/to/output/file.txt");
    }
}