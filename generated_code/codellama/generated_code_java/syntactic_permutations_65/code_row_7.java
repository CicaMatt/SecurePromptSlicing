import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;

public class UploadServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    // Check that we have a file upload request
    if (!ServletFileUpload.isMultipartContent(request)) {
      throw new IllegalArgumentException("The request is not a file upload.");
    }

    // Create a factory for disk-based file items
    FileItemFactory factory = new DiskFileItemFactory();

    // Create a new file upload handler
    ServletFileUpload upload = new ServletFileUpload(factory);

    // Parse the request
    List<FileItem> items = upload.parseRequest(request);

    for (FileItem item : items) {
      if (!item.isFormField()) {
        String name = new File(item.getName()).getName();
        String path = getServletContext().getInitParameter("uploads");
        File file = new File(path, name);
        item.write(file);
      }
    }
  }
}