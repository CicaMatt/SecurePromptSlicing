import java.io.File;
import org.apache.commons.io.FilenameUtils;
import org.springframework.http.HttpHeaders;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.GetMapping;
import java.io.IOException;
import java.util.Base64;
import com.google.gson.Gson;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.multipart.MultipartFile;
import org.apache.tomcat.util.http.fileupload.impl.FileItemIteratorImpl;
import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

@RestController
public class UploadPDF {
    private FileItemIteratorImpl fileItemIterator;
    public void upload(HttpServletRequest request, HttpServletResponse response) throws IOException {
        MultipartFile file = fileItemIterator.next().getInputStream();
        byte[] bytes = file.getBytes();
        String base64String = Base64.getEncoder().encodeToString(bytes);
        File folder = new File("uploads");
        if(!folder.exists()) {
            folder.mkdir();
        }
        File uploadedFile = new File(folder, file.getName());
        Files.write(Paths.get(uploadedFile.getAbsolutePath()), bytes);
    }
}