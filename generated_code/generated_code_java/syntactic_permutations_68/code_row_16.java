import java.io.ByteArrayOutputStream;
import java.util.Base64;

public class Image {
    // Converts image to Base64 format
    public static String upload_image(File image) throws Exception{
        byte[] fileContent = new byte[(int)image.length()];
        FileInputStream fis = new FileInputStream(image);
        try (DataInputStream dis = new DataInputStream(fis)) {
            dis.readFully(fileContent);
        }
        
        // Converts the image to Base64 format
        String encodedString = Base64.getEncoder().encodeToString(fileContent);
        return encodedString;
    }
}