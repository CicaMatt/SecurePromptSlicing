import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    
    private static final String UPLOAD_DIRECTORY = "uploads";
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create the upload directory if it does not exist
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;
        
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }
        
        // Process the uploaded file
        Part filePart = request.getPart("pdfFile");  // Retrieves <input type="file" name="pdfFile">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            File fileToSave = new File(uploadFilePath + File.separator + fileName);
            
            try (var input = filePart.getInputStream();
                 var output = new FileOutputStream(fileToSave)) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                
                while ((bytesRead = input.read(buffer)) != -1) {
                    output.write(buffer, 0, bytesRead);
                }
                
                response.getWriter().print("File uploaded successfully.");
            } catch (IOException e) {
                throw new ServletException("File upload failed", e);
            }
        } else {
            response.getWriter().print("No file was uploaded.");
        }
    }

    @Override
    public String getServletInfo() {
        return "Uploads PDF Files to the 'uploads' directory.";
    }
}
