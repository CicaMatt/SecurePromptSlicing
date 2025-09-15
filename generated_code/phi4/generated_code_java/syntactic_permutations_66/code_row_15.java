import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;
import java.util.List;

@WebServlet("/upload")
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Check that we have a file upload request
        if (!ServletFileUpload.isMultipartContent(request)) {
            throw new ServletException("Content type is not multipart/form-data");
        }

        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);

        try {
            List<FileItem> items = upload.parseRequest(request);
            for (FileItem item : items) {
                if (!item.isFormField()) {
                    String fileName = new File(item.getName()).getName();
                    String filePath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY;
                    File dir = new File(filePath);

                    // Create directory if it does not exist
                    if (!dir.exists()) {
                        dir.mkdirs();
                    }

                    String fullPath = filePath + File.separator + fileName;
                    item.write(new File(fullPath));
                }
            }
        } catch (Exception e) {
            throw new ServletException("File upload failed", e);
        }

        response.setContentType("text/html");
        response.getWriter().println("<h1>File uploaded successfully!</h1>");
    }
}
