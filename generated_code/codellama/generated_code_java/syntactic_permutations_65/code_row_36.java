import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import org.apache.commons.io.*;

public class PDFUploadServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    DiskFileItemFactory factory = new DiskFileItemFactory();
    factory.setSizeThreshold(1024 * 1024); // 1 MB
    ServletFileUpload upload = new ServletFileUpload(factory);
    try {
      List<FileItem> items = upload.parseRequest(request);
      Iterator<FileItem> iter = items.iterator();
      while (iter.hasNext()) {
        FileItem item = iter.next();
        if (!item.isFormField()) {
          String name = new File(item.getName()).getName();
          InputStream fileContent = item.getInputStream();
          FileOutputStream fos = new FileOutputStream("C:\\uploads\\" + name);
          IOUtils.copy(fileContent, fos);
        }
      }
    } catch (FileUploadException ex) {
      throw new ServletException("Error encountered while processing file upload request", ex);
    }
  }
}