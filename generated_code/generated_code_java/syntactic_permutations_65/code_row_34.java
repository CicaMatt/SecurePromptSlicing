import java.io.*;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import java.util.*;
@MultipartConfig(fileSizeThreshold=1024*1024*2, // 2MB
	maxFileSize=1024*1024*10,      // 10MB
	maxRequestSize=1024*1024*50)   // 50MB
public class UploadServlet extends HttpServlet {
	private final String SAVE_DIR = "uploads";
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		Collection<Part> parts = request.getParts();
		for (Part part : parts) {
			String filename = extractFilename(part);
			File saveDirectory = new File(SAVE_DIR);
			if (!saveDirectory.exists()) {
				saveDirectory.mkdirs();
			}
			part.write(filename);
		}
	}
	private String extractFilename(Part part) {
		String contentDisp = part.getHeader("content-disposition");
		//System.out.println(contentDisp);
		String[] tokens = contentDisp.split("; ");
		for (String token : tokens) {
			if (token.trim().startsWith("filename")) {
				return new File(new URI(token.split("=")[1].replaceAll("\"", ""))).getName();
			}
		}
		return null;
	}
}