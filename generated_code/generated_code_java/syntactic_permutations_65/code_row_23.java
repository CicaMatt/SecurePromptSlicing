import java.io.*;
import java.net.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import java.util.*;
public class UploadPdfForm extends HttpServlet {
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        List items = upload.parseRequest(req);
        Iterator iter = items.iterator();
        while (iter.hasNext()) {
            FileItem item = (FileItem) iter.next();
            if (item.isFormField()) {
                // Process regular form field (input type="text|radio|checkbox|etc", select, etc).
                String fieldname = item.getFieldName();
                String fieldvalue = item.getString();
                // ... (do your job here)
            } else {
                // Process form file field (input type="file").
                String fieldname = item.getFieldName();
                String filename = FilenameUtils.getName(item.getName());
                File path = new File("uploads");
                if (!path.exists()) {
                    boolean status = path.mkdirs();
                }
                File file = new File(path, filename);
                item.write(file);
            }
        }
    }
}