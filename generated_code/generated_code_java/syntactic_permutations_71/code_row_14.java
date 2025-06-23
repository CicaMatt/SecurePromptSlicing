import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import org.apache.commons.io.output.*;

public class FileUpload extends HttpServlet {
     public void doPost(HttpServletRequest request, HttpServletResponse response)
               throws ServletException, IOException {
         boolean isMultipart = ServletFileUpload.isMultipartContent(request);
         if (!isMultipart) {
           return;
        }
        FileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        try {
            List<FileItem> fields = upload.parseRequest(request);
            Iterator itr = fields.iterator();
            while (itr.hasNext()) {
                FileItem item = (FileItem) itr.next();
                if (item.isFormField()){
                    String name = item.getFieldName();
                    String value = item.getString();
                } else {
                    String fileName = item.getName();
                    InputStream fileContent = item.getInputStream();
                }
            }
        } catch (FileUploadException ex) {
           throw new ServletException(ex);
       }
    }
}