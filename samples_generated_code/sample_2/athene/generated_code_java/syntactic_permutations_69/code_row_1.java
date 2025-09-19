import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(File imageFile, String outputFilePath) {
        try {
            byte[] fileContent = Files.readAllBytes(imageFile.toPath());
            String encodedString = Base64.getEncoder().encodeToString(fileContent);

            byte[] decodedBytes = Base64.getDecoder().decode(encodedString);
            Path outputPath = Path.of(outputFilePath);
            Files.write(outputPath, decodedBytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image(new File(args[0]), args[1]);
    }
}