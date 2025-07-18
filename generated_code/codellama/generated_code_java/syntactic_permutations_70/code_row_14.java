import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
 
public class FileUpload extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String DIR_PATH = "C:\\uploads\\";
 
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        boolean isMultipart = ServletFileUpload.isMultipartContent(request);
        if (isMultipart) {
            DiskFileItemFactory factory = new DiskFileItemFactory();
            factory.setSizeThreshold(1 * 1024 * 1024); // 1 MB
 
            ServletFileUpload uploader = new ServletFileUpload(factory);
            try {
                List<FileItem> items = uploader.parseRequest(request);
                Iterator<FileItem> iter = items.iterator();
 
                while (iter.hasNext()) {
                    FileItem item = iter.next();
                    if (item.isFormField()) {
                        processFormField(item, request, response);
                    } else {
                        processFileField(item);
                    }
                }
            } catch (FileUploadException ex) {
                throw new ServletException("Could not parse multipart request", ex);
            }
        } else {
            throw new ServletException("Request is not a multipart request");
        }
    }
 
    private void processFormField(FileItem item, HttpServletRequest request,
            HttpServletResponse response) throws UnsupportedEncodingException {
        String fieldName = item.getFieldName();
        String value = item.getString("UTF-8");
 
        System.out.println(fieldName + "=" + value);
    }
 
    private void processFileField(FileItem item) throws IOException {
        String fileName = item.getName();
        boolean isInMemory = item.isInMemory();
 
        if (fileName != null && !fileName.isEmpty()) {
            File file = new File(DIR_PATH + fileName);
 
            try {
                item.write(file);
                System.out.println("File uploaded successfully");
            } catch (Exception ex) {
                throw new IOException("Could not write file to the disk", ex);
            }
        }
    }
}