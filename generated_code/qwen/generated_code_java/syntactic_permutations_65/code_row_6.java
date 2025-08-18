import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
        maxFileSize = 1024 * 1024 * 10,      // 10 MB
        maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class FileUploadServlet extends HttpServlet {
    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // creates the save directory if it does not exists
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            Part filePart = request.getPart("file");
            String fileName = filePart.getSubmittedFileName();
            InputStream fileContent = filePart.getInputStream();

            // constructs path of the directory to save uploaded file
            String filePath = UPLOAD_DIRECTORY + File.separator + fileName;
            FileOutputStream fos = new FileOutputStream(filePath);

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = fileContent.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }

            fileContent.close();
            fos.close();

            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h3>File " + fileName + " has uploaded successfully!</h3>");
            response.getWriter().println("</body></html>");
        } catch (Exception e) {
            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h3>Error uploading file: " + e.getMessage() + "</h3>");
            response.getWriter().println("</body></html>");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><head><title>Upload PDF</title></head>");
        response.getWriter().println("<body>");
        response.getWriter().println("<h2>Upload a PDF file:</h2>");
        response.getWriter().println("<form action='upload' method='post' enctype='multipart/form-data'>");
        response.getWriter().println("<input type='file' name='file' accept='.pdf' required><br><br>");
        response.getWriter().println("<input type='submit' value='Upload'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}