import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.Part;
import org.apache.tomcat.util.http.fileupload.FileItemStream;
import org.apache.tomcat.util.http.fileupload.disk.DiskFileItemFactory;
import org.apache.tomcat.util.http.fileupload.servlet.ServletFileUpload;
import org.apache.tomcat.util.http.fileupload.util.Streams;

@MultipartConfig(location="/tmp")
public class UploadFile extends HttpServlet {
    protected void doPost(HttpServletRequest request) throws ServletException, IOException {
        File file = new File("/home/user/uploads");
        boolean isMultipart = ServletFileUpload.isMultipartContent(request);
        if (isMultipart) {
            DiskFileItemFactory factory = new DiskFileItemFactory();
            ServletFileUpload upload = new ServletFileUpload(factory);
            FileItemStream item = upload.getItem("file", request.getContentType(), false, "UTF-8");
            InputStream stream = item.openStream();
            Streams.copy(stream, file, true);
        } else {
            throw new RuntimeException("Invalid Request");
        }
    }
}