import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/file")
public class FileServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String filePath = request.getParameter("file");
        
        if (filePath != null && !filePath.isEmpty()) {
            Path path = Path.of(filePath);
            
            try (var inputStream = Files.newInputStream(path)) {
                byte[] fileData = inputStream.readAllBytes();
                
                response.setContentType(getServletContext().getMimeType(path.toString()));
                response.setContentLength(fileData.length);
                response.getOutputStream().write(fileData);
            } catch (IOException e) {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found or could not be read.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing 'file' parameter in URL.");
        }
    }
}