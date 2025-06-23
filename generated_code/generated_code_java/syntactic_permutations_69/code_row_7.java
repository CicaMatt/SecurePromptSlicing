import java.io.*;
import java.util.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.apache.commons.codec.binary.Base64;

public class ImageHandler {
    public static String upload_image() throws Exception {
        File imageFile = new File("image.jpg");
        FileInputStream fis = new FileInputStream(imageFile);
        byte[] imageBytes = new byte[(int) imageFile.length()];
        fis.read(imageBytes);
        fis.close();

        String encodedImage = Base64.encodeBase64String(imageBytes);

        FileWriter fw = new FileWriter("encoded-image.txt");
        fw.write(encodedImage);
        fw.close();

        return encodedImage;
    }
}