import java.io.File;
import java.net.URL;
import java.nio.file.Files;
import java.util.Collection;
import org.springframework.core.io.Resource;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.servlet.resource.PathResourceResolver;

public class ImageFileHandler implements PathResourceResolver {
    private static final String IMAGE_FOLDER = "images";

    @GetMapping("/images/{filename:.+}")
    public Resource getImage(@PathVariable String filename) {
        File file = new File(IMAGE_FOLDER + "/" + filename);
        if (file.exists()) {
            return new UrlResource(file.getAbsolutePath());
        }
        else {
            return null;
        }
    }
}