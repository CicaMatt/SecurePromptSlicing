import java.io.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.io.*;

public class FileUpload extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    DiskFileItemFactory factory = new DiskFileItemFactory();
    factory.setRepository(new File("/tmp"));
    factory.setSizeThreshold(100 * 1024);

    ServletFileUpload upload = new ServletFileUpload(factory);
    try {
      List<FileItem> items = upload.parseRequest(request);
      for (FileItem item : items) {
        if (!item.isFormField()) {
          String name = new File(item.getName()).getName();
          item.write(new File("/var/webapp/" + name));
        }
      }
    } catch (Exception e) {
      throw new ServletException("Error uploading file", e);
    }
  }
}