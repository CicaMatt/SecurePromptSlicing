import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getParameter("name");
        if (imageName == null || imageName.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing 'name' parameter.");
            return;
        }

        File imageFile = new File(getServletContext().getRealPath("/images"), imageName);
        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            return;
        }

        response.setContentType(getServletContext().getMimeType(imageName));
        try (OutputStream out = response.getOutputStream();
             FileInputStream in = new FileInputStream(imageFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = in.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }
        }
    }

    public static void main(String[] args) {
        // This is just for standalone testing. In a real application, you would deploy this servlet to a web container.
        System.out.println("ImageServlet ready to be deployed.");
    }
}


Note: To run this code in an actual Java web application, you need to configure it properly in your `web.xml` or use annotations and ensure that the servlet is part of a running servlet container like Apache Tomcat. The file path `/images/` should exist within your web application context directory.