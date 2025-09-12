import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(String imagePath, String outputFilePath) {
        try (FileInputStream fis = new FileInputStream(imagePath)) {
            byte[] imageBytes = new byte[fis.available()];
            fis.read(imageBytes);
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            writeEncodedImageToFile(encodedImage, outputFilePath);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void writeEncodedImageToFile(String encodedImage, String outputFilePath) {
        try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            byte[] decodedImage = Base64.getDecoder().decode(encodedImage);
            fos.write(decodedImage);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        String imagePath = "path/to/input/image.jpg";
        String outputFilePath = "path/to/output/image.jpg";
        uploader.upload_image(imagePath, outputFilePath);
    }
}