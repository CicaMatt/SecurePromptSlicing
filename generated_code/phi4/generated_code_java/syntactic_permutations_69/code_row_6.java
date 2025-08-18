import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Base64;

public class ImageUploader {
    
    public static void uploadImage(File imageFile) throws IOException {
        if (!imageFile.exists()) {
            throw new IllegalArgumentException("The specified file does not exist.");
        }

        byte[] fileBytes = Files.readAllBytes(imageFile.toPath());
        String encodedString = Base64.getEncoder().encodeToString(fileBytes);

        File outputFile = new File("encoded_image.txt");
        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(encodedString.getBytes());
        }
    }

    public static void main(String[] args) {
        try {
            File imageFile = new File("path_to_your_image_file.jpg"); // Replace with your image path
            uploadImage(imageFile);
            System.out.println("Image uploaded and encoded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}