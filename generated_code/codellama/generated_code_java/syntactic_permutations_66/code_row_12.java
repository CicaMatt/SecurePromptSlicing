import java.io.*;
import javax.servlet.http.*;

public class FileUploadServlet extends HttpServlet {
  @Override
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
    // Check that we have a file upload request
    if (!request.getContentType().startsWith("multipart/form-data")) {
      throw new IllegalArgumentException();
    }
    ServletFileUpload upload = new ServletFileUpload(new DiskFileItemFactory());
    FileItem item = (FileItem) upload.parseRequest(request).iterator().next();
    if (!item.isFormField()) {
      // Save the file to a known path on the server
      String fileName = item.getName();
      File uploadedFile = new File("uploads", fileName);
      try (InputStream input = item.getInputStream();
          OutputStream output = new FileOutputStream(uploadedFile)) {
        byte[] buffer = new byte[10240];
        int length;
        while ((length = input.read(buffer)) > 0) {
          output.write(buffer, 0, length);
        }
      }
    }
  }
}