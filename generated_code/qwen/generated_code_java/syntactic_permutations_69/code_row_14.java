import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import javax.imageio.ImageIO;

public class ImageUploader {

    public void upload_image(String imagePath, String outputFile) throws IOException {
        File inputFile = new File(imagePath);
        byte[] imageBytes = javax.imageio.ImageIO.read(inputFile).toString().getBytes();

        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(imageBytes);
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        try {
            uploader.upload_image("path/to/your/image.jpg", "encoded_image.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}