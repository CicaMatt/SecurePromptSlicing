import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(urlPatterns = "/img")
public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getPathInfo().substring(1); // Get the filename from URL path
        File file = new File("images/" + name);

        if (file.exists() && !file.isDirectory()) {
            response.setContentType(getServletContext().getMimeType(file.getName()));
            ServletOutputStream out = response.getOutputStream();
            try (InputStream in = new FileInputStream(file)) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = in.read(buffer)) != -1) {
                    out.write(buffer, 0, bytesRead);
                }
            } finally {
                out.close();
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND); // 404 error
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}