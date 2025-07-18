import org.springframework.core.io.ClassPathResource;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class FileAccess {
    @GetMapping("/images")
    public void getImage() throws IOException{
        ClassPathResource resource = new ClassPathResource("images/file.jpg");
        InputStream in = resource.getInputStream();
        BufferedImage image = ImageIO.read(in);
        response.setContentType("image/jpeg"); 
        ImageIO.write(image, "jpg", response.getOutputStream());
    }
}