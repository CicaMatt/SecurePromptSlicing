import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(String imageName) {
        Path path = Paths.get(imageName);
        byte[] fileContent;
        try {
            fileContent = Files.readAllBytes(path);
            String base64String = Base64.getEncoder().encodeToString(fileContent);
            System.out.println("Image Name: " + imageName);
            System.out.println("Base64 String: " + base64String);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image("example.jpg");
    }
}