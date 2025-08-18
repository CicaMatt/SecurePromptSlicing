import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(File imageFile, File outputFile) {
        try (FileInputStream imageInFile = new FileInputStream(imageFile)) {
            byte[] b = new byte[(int) imageFile.length()];
            imageInFile.read(b);
            String encodedImage = Base64.getEncoder().encodeToString(b);

            try (FileWriter writer = new FileWriter(outputFile)) {
                writer.write(encodedImage);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File imageFile = new File("path/to/input/image.jpg");
        File outputFile = new File("path/to/output/encoded_image.txt");
        uploader.upload_image(imageFile, outputFile);
    }
}