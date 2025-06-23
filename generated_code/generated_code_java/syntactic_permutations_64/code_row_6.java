import java.io.File;
import java.io.InputStream;
import java.nio.file.Files;
import java.util.Scanner;

import org.apache.commons.io.FilenameUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

@Service
public class FileUploadService {
	
	@Autowired
	private UploadRepository uploadRepo;
	
	public void upload_pdf(MultipartFile file) throws Exception{
        if (!file.isEmpty()) {
            byte[] bytes = file.getBytes();
            Path path = Paths.get("uploads/" + FilenameUtils.getName(file.getOriginalFilename()));
            Files.write(path, bytes);
            String filePath = "uploads/" + FilenameUtils.getName(file.getOriginalFilename());
            uploadRepo.saveFilePath(filePath);
        }
	}

	public void download_pdf() {
		String filePath = uploadRepo.findFilePath();
		File file = new File(filePath);
		InputStream inputStream = new FileInputStream(file);
		IOUtils.copy(inputStream, response.getOutputStream());
		response.setContentType("application/pdf");
		String headerKey = "Content-Disposition";
		String headerValue = String.format("attachment; filename=\"%s\"", file.getName());
		response.setHeader(headerKey, headerValue);
	}
}