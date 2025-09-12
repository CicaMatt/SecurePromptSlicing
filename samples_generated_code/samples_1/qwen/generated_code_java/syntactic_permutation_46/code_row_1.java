import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name parameter is required");
            return;
        }
        
        File file = new File(name);
        if (!file.exists() || !file.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
            return;
        }

        try (FileInputStream inStream = new FileInputStream(file)) {
            String mimeType = getServletContext().getMimeType(name);
            if (mimeType == null) {
                mimeType = "application/octet-stream";
            }
            response.setContentType(mimeType);
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inStream.read(buffer)) != -1) {
                response.getOutputStream().write(buffer, 0, bytesRead);
            }
        }
    }
}