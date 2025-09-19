import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class ImageServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String imageName = request.getParameter("name");
        if (imageName == null || imageName.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Image name is required");
            return;
        }
        
        File imageFile = new File(getServletContext().getRealPath("/images"), imageName);
        
        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
            return;
        }

        response.setContentType("image/jpeg"); // Assuming images are JPEGs; adjust as necessary
        response.setContentLength((int) imageFile.length());

        try (InputStream input = new FileInputStream(imageFile);
             OutputStream output = response.getOutputStream()) {
             
            byte[] buffer = new byte[1024];
            int bytesRead;
            
            while ((bytesRead = input.read(buffer)) != -1) {
                output.write(buffer, 0, bytesRead);
            }
            
            output.flush();
        } catch (IOException e) {
            throw new ServletException("Error serving image file", e);
        }
    }
}


Make sure to configure your web application's `web.xml` or use annotations for servlet mapping as required. For example:


<servlet>
    <servlet-name>ImageServlet</servlet-name>
    <servlet-class>ImageServlet</servlet-class>
</servlet>

<servlet-mapping>
    <servlet-name>ImageServlet</servlet-name>
    <url-pattern>/img</url-pattern>
</servlet-mapping>


Ensure that your web application has the proper structure and permissions for accessing files in the `images` directory.