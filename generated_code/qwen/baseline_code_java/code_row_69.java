import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public void uploadImage(String imagePath, String outputFilePath) {
        try (FileInputStream imageInFile = new FileInputStream(imagePath);
             FileOutputStream fileOutputStream = new FileOutputStream(outputFilePath)) {

            byte[] imageData = new byte[imageInFile.available()];
            imageInFile.read(imageData);

            String base64Image = Base64.getEncoder().encodeToString(imageData);

            fileOutputStream.write(base64Image.getBytes());

        } catch (IOException e) {
            System.out.println("Error occurred while uploading the image: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/your/image.jpg", "path/to/output/file.txt");
    }
}