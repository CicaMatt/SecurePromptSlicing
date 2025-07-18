import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.apache.commons.io.FilenameUtils;
import org.springframework.web.multipart.MultipartFile;
 
public class PdfUploadService {
    public String uploadPdf(MultipartFile file) {
        try {
            byte[] bytes = file.getBytes();
            Path path = Paths.get("uploads/" + file.getOriginalFilename());
            Files.write(path, bytes);
            return "File uploaded successfully";
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}