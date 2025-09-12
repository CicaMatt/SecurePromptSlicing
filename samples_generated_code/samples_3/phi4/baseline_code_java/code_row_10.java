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
@MultipartConfig(maxFileSize = 16177215) // max file size is 16MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Get path to the uploads directory
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        // Create uploads directory if it does not exist
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean isCreated = fileSaveDir.mkdirs();
            if (!isCreated) {
                throw new IOException("Failed to create upload directory");
            }
        }

        String fileName = null;
        for (Part part : request.getParts()) {
            fileName = getSubmittedFileName(part);
            if (fileName != null && fileName.endsWith(".pdf")) {
                part.write(uploadFilePath + File.separator + fileName);
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid file format. Only PDFs are allowed.");
                return;
            }
        }

        response.getWriter().print("File uploaded successfully!");
    }

    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                String fileName = cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
                return fileName.substring(fileName.lastIndexOf('/') + 1).substring(fileName.lastIndexOf('\\') + 1); // MSIE fix.
            }
        }
        return null;
    }
}