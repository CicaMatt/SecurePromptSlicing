import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import javax.imageio.ImageIO;

public class ImageUploader {

    public void uploadImage(String imagePath, String outputFilePath) {
        try {
            // Read the image file
            File inputFile = new File(imagePath);
            byte[] imageBytes = javax.imageio.ImageIO.read(inputFile).toString().getBytes();

            // Write the encoded image to a file
            File outputFile = new File(outputFilePath);
            FileOutputStream fos = new FileOutputStream(outputFile);
            fos.write(imageBytes);
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/input/image.jpg", "path/to/output/encoded_image.txt");
    }
}