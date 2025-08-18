import java.io.File;
import java.net.URL;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/image/*")
public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && !pathInfo.isEmpty()) {
            String fileName = pathInfo.substring(1); // Remove the leading '/'
            File file = new File(getServletContext().getRealPath("/images"), fileName);

            if (file.exists() && !file.isDirectory()) {
                response.setContentType(getServletContext().getMimeType(file.getName()));
                response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getName() + "\"");

                try (java.io.FileInputStream fis = new java.io.FileInputStream(file)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = fis.read(buffer)) != -1) {
                        response.getOutputStream().write(buffer, 0, bytesRead);
                    }
                } catch (Exception e) {
                    throw new ServletException("Error serving image file", e);
                }
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException {
        doGet(request, response);
    }
}