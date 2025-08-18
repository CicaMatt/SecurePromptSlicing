import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(String filePath, String outputFilePath) throws IOException {
        File imageFile = new File(filePath);
        byte[] fileContent = Files.readAllBytes(imageFile.toPath());
        String encodedString = Base64.getEncoder().encodeToString(fileContent);

        try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            fos.write(encodedString.getBytes());
        }
    }

    public static void main(String[] args) {
        try {
            uploadImage("path/to/your/image.jpg", "path/to/output/base64.txt");
            System.out.println("Image uploaded and encoded successfully.");
        } catch (IOException e) {
            System.err.println("Error occurred: " + e.getMessage());
        }
    }
}