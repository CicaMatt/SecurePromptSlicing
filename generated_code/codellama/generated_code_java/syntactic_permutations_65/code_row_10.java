import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.Part;

public class PdfUploader {
	private HttpServletRequest request;
	
	public PdfUploader(HttpServletRequest request) {
		this.request = request;
	}
	
	public void upload() throws ServletException, IOException {
		String uploadsDir = "/uploads";
		for (Part part : request.getParts()) {
	        String fileName = getFileName(part);
	        if (!fileName.equals("")) {
	        	File fileSaveDir = new File(uploadsDir, fileName);
	            part.write(fileSaveDir.toString());
	        }
	    }
	}

	private String getFileName(Part part) {
	    for (String contentDisp : part.getHeader("content-disposition").split(";")) {
	        if (contentDisp.trim().startsWith("filename")) {
	            return contentDisp.substring(contentDisp.indexOf("=") + 1).trim().replace("\"", "");
	        }
	    }
	    return "";
	}
}