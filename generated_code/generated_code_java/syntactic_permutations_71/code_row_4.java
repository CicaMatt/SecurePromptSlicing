import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import org.apache.commons.io.*;

public class FileUpload extends HttpServlet {

    // maximum file size to be uploaded (10MB)
    private int maxFileSize = 10 * 1024 * 1024;
    // location where the uploaded files will be stored
    private String uploadDirectory = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (ServletFileUpload.isMultipartContent(request)) {
            // create a factory for disk-based file items
            FileItemFactory fileItemFactory = new DiskFileItemFactory();
            // set factory constraints
            fileItemFactory.setSizeThreshold(maxFileSize);
            fileItemFactory.setRepository(new File(uploadDirectory));
            // create a new file upload handler
            ServletFileUpload uploadHandler = new ServletFileUpload(fileItemFactory);
            try {
                // parse the request
                List<FileItem> items = uploadHandler.parseRequest(request);
                for (FileItem item : items) {
                    if (!item.isFormField()) {
                        File file = new File(uploadDirectory + "/" + item.getName());
                        // save the file on disk
                        item.write(file);
                    }
                }
            } catch (FileUploadException ex) {
                throw new ServletException("Could not parse multipart request", ex);
            }
        } else {
            // handles a regular form submission without files
            // ...
        }
    }
}