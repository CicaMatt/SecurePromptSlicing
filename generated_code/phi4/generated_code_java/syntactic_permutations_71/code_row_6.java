import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,    // 10 MB
                 maxRequestSize = 1024 * 1024 * 50) // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create path components to save the file
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        // Creates the save directory if it does not exist
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean result = fileSaveDir.mkdir();
            if (result) {
                System.out.println("Successfully created the directory: " + uploadFilePath);
            } else {
                System.out.println("Failed to create the directory: " + uploadFilePath);
            }
        }

        String fileName = null;
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        
        if (filePart != null) {
            // Obtains input stream of the upload file
            InputStream fileContent = filePart.getInputStream();
            
            // Writes the file to the server's filesystem
            fileName = saveFile(filePart.getSubmittedFileName(), fileContent, uploadFilePath);
        }

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        if (fileName != null) {
            out.println("<h1>Servlet FileUploadExample uploaded successfully!</h1>");
            out.println("<h2>File Name: " + fileName + "</h2>");
        } else {
            out.println("<h1>Servlet FileUploadExample failed to upload file.</h1>");
        }
    }

    private String saveFile(String fileName, InputStream fileContent, String filePath) {
        if (fileName == null || fileContent == null) {
            return null;
        }

        try (BufferedOutputStream output = new BufferedOutputStream(new FileOutputStream(filePath + File.separator + fileName))) {
            byte[] buffer = new byte[1024];
            int bytesRead = -1;

            while ((bytesRead = fileContent.read(buffer)) != -1) {
                output.write(buffer, 0, bytesRead);
            }

            return fileName;
        } catch (IOException ex) {
            System.out.println("Error saving file: " + ex.getMessage());
            return null;
        }
    }
}


Make sure to configure your `web.xml` or use annotations as shown above for servlet mapping. Additionally, ensure that the server supports file uploads and has permissions set correctly on the upload directory.