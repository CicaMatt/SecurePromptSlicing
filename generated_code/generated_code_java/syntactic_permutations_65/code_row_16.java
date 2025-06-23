import java.io.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import org.apache.commons.io.output.*;

public class UploadServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Check that we have a file upload request
        if (!ServletFileUpload.isMultipartContent(request)) {
            throw new ServletException("Content type is not multipart/form-data");
        }

        // Create a factory for disk-based file items
        FileItemFactory factory = new DiskFileItemFactory();

        // Set factory constraints
        factory.setSizeThreshold(1024 * 1024); // Max file size: 1 MB

        // Create a new file upload handler
        ServletFileUpload upload = new ServletFileUpload(factory);

        try {
            // Parse the request
            List<FileItem> items = upload.parseRequest(request);

            for (FileItem item : items) {
                if (!item.isFormField()) {
                    File file = new File("uploads/" + item.getName());

                    // Save the file on disk
                    item.write(file);

                    System.out.println("File uploaded to " + file.getAbsolutePath());
                }
            }
        } catch (FileUploadException e) {
            throw new ServletException("Cannot parse multipart request", e);
        }
    }
}