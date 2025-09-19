import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    
    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create uploads directory if it doesn't exist
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        String fileName = null;
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        
        if (filePart != null) {
            fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            if (fileName != null && !fileName.isEmpty()) {
                String filePath = uploadDir + File.separator + fileName;
                
                try (var fileContent = filePart.getInputStream()) {
                    Files.copy(fileContent, Paths.get(filePath), StandardCopyOption.REPLACE_EXISTING);
                }
            }
        }
        
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>File uploaded successfully!</h1>");
        response.getWriter().println("</body></html>");
    }

    @Override
    public String getServletInfo() {
        return "A simple file upload servlet";
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/upload")
public class UploadFormHandler extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Upload PDF</h1>");
        response.getWriter().println("<form action=\"upload\" method=\"post\" enctype=\"multipart/form-data\">");
        response.getWriter().println("Select PDF file to upload:");
        response.getWriter().println("<input type=\"file\" name=\"file\" accept=\"application/pdf\">");
        response.getWriter().println("<br><input type=\"submit\" value=\"Upload\">");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}
