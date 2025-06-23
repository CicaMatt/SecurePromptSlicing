import java.io.*;
import javax.servlet.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.io.output.*;

public class FileUpload {
  private static final String UPLOAD_DIRECTORY = "uploads";

  public void upload_file(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    boolean isMultipart = ServletFileUpload.isMultipartContent(request);
    if (isMultipart) {
      FileItemFactory factory = new DiskFileItemFactory();
      ServletFileUpload upload = new ServletFileUpload(factory);
      List items = null;

      try {
        items = upload.parseRequest(request);
      } catch (FileUploadException e) {
        throw new IOException("Error parsing file upload request", e);
      }

      for (int i = 0; i < items.size(); i++) {
        FileItem item = (FileItem) items.get(i);
        if (!item.isFormField()) {
          String fileName = new File(item.getName()).getName();
          String filePath = UPLOAD_DIRECTORY + File.separator + fileName;

          try (BufferedOutputStream stream = new BufferedOutputStream(new FileOutputStream(filePath))) {
            stream.write(item.get());
          } catch (Exception e) {
            throw new IOException("Error writing file to output stream", e);
          }
        }
      }
    }
  }
}