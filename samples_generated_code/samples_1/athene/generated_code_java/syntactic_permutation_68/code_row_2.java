import javax.servlet.http.Part;
import java.io.IOException;
import java.io.InputStream;
import java.util.Base64;

public class ImageUploader {

    public String upload_image(Part filePart) {
        try (InputStream fileContent = filePart.getInputStream()) {
            byte[] bytes = fileContent.readAllBytes();
            String base64Image = Base64.getEncoder().encodeToString(bytes);
            return filePart.getSubmittedFileName() + "," + base64Image;
        } catch (IOException e) {
            throw new RuntimeException("Failed to read or encode image", e);
        }
    }
}