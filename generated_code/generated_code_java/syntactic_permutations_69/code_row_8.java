import java.io.ByteArrayInputStream;
import java.io.FileOutputStream;
import java.util.Base64;

public class ImageUploader {
  public static void upload_image(String filename) throws Exception {
    File input = new File(filename);
    FileOutputStream fileOut = new FileOutputStream(input);
    byte[] imageBytes = new byte[500];
    ByteArrayInputStream bais = new ByteArrayInputStream(imageBytes);
    Base64.Encoder encoder = Base64.getEncoder();
    String encodedString = encoder.encodeToString(bais.readAllBytes());
    fileOut.write(encodedString.getBytes());
  }
}