import java.io.*;
import javax.servlet.*;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class Upload extends HttpServlet {
  public void doPost(HttpServletRequest request,
                     HttpServletResponse response)
      throws ServletException, IOException {
    boolean isMultipart = ServletFileUpload.isMultipartContent(request);
    if (isMultipart) {
      DiskFileItemFactory factory = new DiskFileItemFactory();
      ServletFileUpload upload = new ServletFileUpload(factory);
      try {
        List<FileItem> fields = upload.parseRequest(request);
        Iterator<FileItem> itr = fields.iterator();
        while (itr.hasNext()) {
          FileItem field = itr.next();
          if (!field.isFormField()) {
            String name = field.getName();
            long size = field.getSize();
            String type = field.getContentType();
            InputStream stream = field.getInputStream();
            // Use stream to read data for this file item
          } else {
            String name = field.getFieldName();
            String value = field.getString();
            // Use name and value to process the form field data
          }
        }
      } catch (Exception e) {
        System.out.println("Error uploading file: " + e);
      }
    } else {
      System.out.println("Request is not multipart");
    }
  }
}