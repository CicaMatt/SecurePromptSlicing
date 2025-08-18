import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(String imagePath, String outputFilePath) {
        try (FileInputStream imageInFile = new FileInputStream(imagePath)) {
            byte[] imageData = new byte[(int) new File(imagePath).length()];
            imageInFile.read(imageData);
            String encodedImage = Base64.getEncoder().encodeToString(imageData);
            try (FileOutputStream fileOutStream = new FileOutputStream(outputFilePath)) {
                fileOutStream.write(encodedImage.getBytes());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image("path/to/input/image.jpg", "path/to/output/encoded-image.txt");
    }
}