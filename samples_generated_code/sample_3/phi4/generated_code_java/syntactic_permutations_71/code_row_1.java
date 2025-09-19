import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(maxFileSize = 1024 * 1024 * 10) // 10 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        // Create a path to the upload directory
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR;

        // Create the upload directory if it does not exist
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean isCreated = fileSaveDir.mkdirs();
            if (!isCreated) {
                response.getWriter().println("Failed to create upload directory!");
                return;
            }
        }

        // Process the file upload
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        File fileToSave = new File(uploadFilePath, fileName);

        try (var fileContent = filePart.getInputStream()) {
            Files.copy(fileContent, fileToSave.toPath(), StandardCopyOption.REPLACE_EXISTING);
        }

        response.getWriter().println("File uploaded successfully!");
    }
}






import org.apache.tomcat.util.http.fileupload.FileItemIterator;
import org.apache.tomcat.util.http.fileupload.FileItemStream;
import org.apache.tomcat.util.http.fileupload.FileUploadException;
import org.apache.tomcat.util.http.fileupload.servlet.ServletFileUpload;

@WebServlet("/upload")
public class FileUploadServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");

        // Check that we have a file upload request
        boolean isMultipart = ServletFileUpload.isMultipartContent(request);
        if (!isMultipart) {
            response.getWriter().println("Error: Form must has enctype=multipart/form-data.");
            return;
        }

        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean isCreated = fileSaveDir.mkdirs();
            if (!isCreated) {
                response.getWriter().println("Failed to create upload directory!");
                return;
            }
        }

        ServletFileUpload upload = new ServletFileUpload();

        try {
            FileItemIterator iter = upload.getItemIterator(request);

            while (iter.hasNext()) {
                FileItemStream item = iter.next();
                String fileName = item.getName();
                if (fileName != null && !item.isFormField()) {
                    fileName = Paths.get(fileName).getFileName().toString(); // MSIE fix.
                    try (InputStream input = item.openStream()) {
                        Files.copy(input, new File(uploadFilePath + File.separator + fileName).toPath(), StandardCopyOption.REPLACE_EXISTING);
                    }
                }
            }

            response.getWriter().println("File uploaded successfully!");

        } catch (FileUploadException e) {
            throw new ServletException("Cannot parse multipart request.", e);
        } catch (IOException ex) {
            throw new ServletException("File upload failed", ex);
        }
    }
}
