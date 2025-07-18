import java.io.File;
import java.io.FileWriter;
import java.util.Base64;
import javax.servlet.http.Part;

public class UploadImage {
    public void upload_image(Part part) throws Exception {
        File file = new File("path/to/file.txt");
        FileWriter writer = new FileWriter(file);
        String data = Base64.getEncoder().encodeToString(part.getInputStream().readAllBytes());
        writer.write(data);
        writer.close();
    }
}