import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
public class FileUploadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Gets absolute path of the web application
        String appPath = request.getServletContext().getRealPath("");
        String uploadFilePath = appPath + File.separator + UPLOAD_DIRECTORY;

        // Creates the save directory if it does not exist
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }
        
        String fileName = null;
        for (Part part : request.getParts()) {
            fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            if (fileName != null) { // fixes NPE by interpolation
                try (var input = part.getInputStream()) {
                    Files.copy(input, Paths.get(uploadFilePath + File.separator + fileName));
                }
            }
        }

        response.getWriter().print("File " + fileName + " is uploaded successfully.");
    }
}
