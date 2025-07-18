import java.io.*;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class Upload {
    public void upload(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        try {
            List<FileItem> fields = upload.parseRequest(request);
            String filename = "";
            for (FileItem field : fields) {
                if (!field.isFormField()) {
                    filename = new File(field.getName()).getName();
                    File file = new File("uploads/" + filename);
                    field.write(file);
                }
            }
        } catch (FileUploadException e) {
            throw new ServletException("Failed to parse multipart request.", e);
        }
    }
}