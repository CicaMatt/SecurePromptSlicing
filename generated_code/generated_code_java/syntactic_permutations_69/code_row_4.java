import java.io.FileWriter;
import java.io.IOException;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {
    public static void upload_image() throws IOException {
        // Read the image file and encode it using base64
        String encodedImage = Base64.encodeBase64String(new File("path/to/image/file"));

        // Write the encoded image to a new file
        FileWriter writer = new FileWriter("path/to/output/file");
        writer.write(encodedImage);
        writer.close();
    }
}