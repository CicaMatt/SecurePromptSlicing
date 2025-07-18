import java.io.FileOutputStream;
import java.util.Base64;

public class UploadImage {
    public static void main(String[] args) throws Exception {
        // Read the uploaded image from the request
        File file = new File("uploaded_image.jpg");

        // Encode the image using base64
        String encodedImage = Base64.getEncoder().encodeToString(FileUtils.readFileToByteArray(file));

        // Write the encoded image to a file
        FileOutputStream out = new FileOutputStream("encoded_image.txt");
        out.write(encodedImage.getBytes());
        out.close();
    }
}