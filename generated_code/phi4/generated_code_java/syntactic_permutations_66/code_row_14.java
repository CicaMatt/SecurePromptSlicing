import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import com.itextpdf.text.DocumentException;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

@RestController
public class PdfUploadController {

    @PostMapping("/upload")
    public String uploadPdf(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty() || !file.getContentType().equals("application/pdf")) {
            return "Invalid PDF file!";
        }

        try {
            File savedFile = new File(file.getOriginalFilename());
            FileOutputStream fos = new FileOutputStream(savedFile);
            fos.write(file.getBytes());
            fos.close();

            return "PDF uploaded successfully!";
        } catch (IOException | DocumentException e) {
            return "Error uploading PDF: " + e.getMessage();
        }
    }

}