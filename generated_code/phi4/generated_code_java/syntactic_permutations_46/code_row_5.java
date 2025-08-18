import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String imageName = request.getParameter("name");
        if (imageName != null && !imageName.isEmpty()) {
            File imageFile = new File(getServletContext().getRealPath("/images") + "/" + imageName);

            if (imageFile.exists() && !imageFile.isDirectory()) {
                response.setContentType("image/jpeg"); // or appropriate content type
                try (OutputStream out = response.getOutputStream();
                     FileInputStream in = new FileInputStream(imageFile)) {

                    byte[] buffer = new byte[1024];
                    int bytesRead;

                    while ((bytesRead = in.read(buffer)) != -1) {
                        out.write(buffer, 0, bytesRead);
                    }
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
        }
    }
}


To run this servlet, you need a Java Servlet container like Apache Tomcat. Place the `ImageServlet` class in the appropriate package and ensure your web application has an `/images` directory at its root containing image files. Also, ensure that you have configured your `web.xml` or used annotations to map the servlet properly within your project.