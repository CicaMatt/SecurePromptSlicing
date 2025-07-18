import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import java.io.File;
import javax.servlet.http.HttpServletRequest;
import java.nio.file.Files;
import java.nio.file.Paths;

@Controller
public class FileUploadController {
    @RequestMapping(value = "/upload", method = RequestMethod.POST)
    public void handleFileUpload(HttpServletRequest request) throws Exception {
        File file = new File("c:/temp/my-uploaded-file");
        Files.copy(request.getInputStream(), Paths.get(file.toURI()));
    }
}