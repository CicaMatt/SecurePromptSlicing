import java.io.File;
import java.io.IOException;

import javax.servlet.http.Part;

public class ImageUpload {
	private static final String UPLOAD_DIRECTORY = "uploads";
	
	private Part imagePart;
	private File uploadedFile;
	
	public void uploadImage() throws IOException {
		if (imagePart != null) {
			String fileName = getFilename(imagePart);
			try (InputStream inputStream = imagePart.getInputStream()) {
				uploadedFile = new File(UPLOAD_DIRECTORY, fileName);
				Files.copy(inputStream, uploadedFile.toPath());
			}
		}
	}
	
	private String getFilename(Part part) {
		String contentDisposition = part.getHeader("content-disposition");
		int index = contentDisposition.indexOf("filename=\"") + 10;
		return contentDisposition.substring(index, contentDisposition.length() - 1);
	}
}