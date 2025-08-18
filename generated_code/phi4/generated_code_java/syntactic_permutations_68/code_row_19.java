import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        try {
            uploadImage("path/to/your/image.jpg", "imageName");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadImage(String imagePath, String imageName) throws IOException {
        File image = new File(imagePath);
        
        if (!image.exists()) {
            System.out.println("File not found: " + imagePath);
            return;
        }

        FileInputStream fileInputStreamReader = new FileInputStream(image);
        byte[] bytes = new byte[(int) image.length()];
        fileInputStreamReader.read(bytes);

        String encodedImage = Base64.getEncoder().encodeToString(bytes);
        
        // Here you would insert the imageName and encodedImage into your storage
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 Encoded Image: " + encodedImage);
    }
}