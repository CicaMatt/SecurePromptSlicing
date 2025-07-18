import org.apache.commons.codec.binary.Base64;
import java.io.ByteArrayInputStream;
import java.io.FileOutputStream;
import javax.imageio.ImageIO;

public class ImageUtil {
  
    public static void upload_image(String image) throws Exception {
        byte[] data = Base64.decodeBase64(image);
        ByteArrayInputStream in = new ByteArrayInputStream(data);
        FileOutputStream out = new FileOutputStream("image.jpg");
        ImageIO.write(ImageIO.read(in), "jpg", out); 
    }
}