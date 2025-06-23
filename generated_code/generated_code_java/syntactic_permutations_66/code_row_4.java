import javax.servlet.ServletContext;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class UploadPDF {

    private final ServletContext servletContext;
    public UploadPDF(ServletContext servletContext) {
        this.servletContext = servletContext;
    }
    
    public String processRequest() {
        boolean isMultipart = ServletFileUpload.isMultipartContent(request);
        if (!isMultipart) {
            return "Error: Not a PDF file";
        }
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        try {
            List items = upload.parseRequest(request);
            FileItem pdfFile = (FileItem) items.get(0);
            if (!pdfFile.getName().endsWith(".pdf")) {
                return "Error: Not a PDF file";
            }
            String savePath = servletContext.getRealPath("/uploads/");
            File dir = new File(savePath);
            if (!dir.isDirectory()) {
                dir.mkdir();
            }
            String savedFile = pdfFile.getName();
            pdfFile.write(new File(dir, savedFile));
            return "PDF file uploaded successfully";
        } catch (Exception e) {
            return "Error: Unable to upload PDF file";
        }
    }
}