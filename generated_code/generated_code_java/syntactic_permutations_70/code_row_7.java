import java.io.IOException;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import org.apache.commons.io.output.*;
public class FileUpload {
    public void doPost(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
        // Check that we have a file upload request
        if (!ServletFileUpload.isMultipartContent(request)) {
            // Report error
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Not a file upload request");
            return;
        }
        // Create a factory for disk-based file items
        FileItemFactory factory = new DiskFileItemFactory();
        // Configure a repository (to ensure a secure temp location is used)
        ServletContext servletContext = this.getServletConfig().getServletContext();
        File repository = (File) servletContext.getAttribute("javax.servlet.context.tempdir");
        factory.setRepository(repository);
        // Create a new file upload handler
        ServletFileUpload upload = new ServletFileUpload(factory);
        // Parse the request
        try {
            List<FileItem> multiparts = upload.parseRequest(request);
            for (FileItem item : multiparts) {
                if (!item.isFormField()) {
                    String name = new File(item.getName()).getName();
                    item.write(new File(UPLOAD_DIRECTORY + File.separator + name));
                }
            }
        } catch (FileUploadException ex) {
            throw new ServletException("Could not parse multipart request", ex);
        }
    }
}