import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImgServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String fileName = request.getParameter("file");
        
        if (fileName == null || fileName.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "File parameter is missing or empty.");
            return;
        }
        
        Path filePath = Paths.get(fileName);

        // Security check to prevent path traversal attacks
        if (!filePath.startsWith(Paths.get(".").toAbsolutePath())) {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "Access denied.");
            return;
        }

        byte[] fileData = Files.readAllBytes(filePath);
        
        response.setContentType("image/*");
        response.setContentLength(fileData.length);
        
        try (var outputStream = response.getOutputStream()) {
            outputStream.write(fileData);
        }
    }
}