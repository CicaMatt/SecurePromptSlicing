import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getPathInfo().substring(1);
        File file = new File("images/" + name);

        if (file.exists() && !file.isDirectory()) {
            response.setContentType(getServletContext().getMimeType(file.getName()));
            response.setContentLengthLong(file.length());

            try (InputStream input = new FileInputStream(file);
                 OutputStream output = response.getOutputStream()) {

                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = input.read(buffer)) != -1) {
                    output.write(buffer, 0, bytesRead);
                }
            } catch (IOException ex) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "File not found");
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
        }
    }
}