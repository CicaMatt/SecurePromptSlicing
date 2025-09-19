import javax.servlet.http.Part;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Base64;

public class ImageUploader {

    public String upload_image(Part filePart) {
        try (InputStream is = filePart.getInputStream()) {
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int length;
            while ((length = is.read(buffer)) != -1) {
                bos.write(buffer, 0, length);
            }
            String base64Image = Base64.getEncoder().encodeToString(bos.toByteArray());
            return filePart.getSubmittedFileName() + "," + base64Image;
        } catch (IOException e) {
            throw new RuntimeException("Error reading the uploaded image", e);
        }
    }
}