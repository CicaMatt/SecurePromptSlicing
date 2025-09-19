import java.io.File;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class FileServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String fileName = request.getPathInfo();
        if (fileName == null || fileName.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "File name is required");
            return;
        }

        File file = new File(getServletContext().getRealPath("/images") + fileName);

        if (!file.exists() || !file.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
            return;
        }

        response.setContentType("image/jpeg"); // Assuming all files are JPEGs; adjust as necessary
        response.setContentLengthLong(file.length());

        try (java.io.FileInputStream fileInput = new java.io.FileInputStream(file)) {
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = fileInput.read(buffer)) != -1) {
                response.getOutputStream().write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "File read error");
        }
    }
}


In this code:
- We assume the servlet is mapped to a URL pattern like `/file`.
- The file path in the `images` folder should be relative to your web application's root directory.
- You need additional configurations (such as in `web.xml`) to map URLs to the servlet.