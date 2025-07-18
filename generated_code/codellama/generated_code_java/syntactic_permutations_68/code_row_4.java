import java.io.File;
import java.io.IOException;
import java.util.Base64;

public class ImageUpload {
  public static void uploadImage() throws IOException {
    File file = new File("image.png");
    String imageName = "image.png";
    byte[] imageBytes = Base64.getEncoder().encode(file);
    String base64String = new String(imageBytes, "UTF-8");
    System.out.println(base64String);
  }
}