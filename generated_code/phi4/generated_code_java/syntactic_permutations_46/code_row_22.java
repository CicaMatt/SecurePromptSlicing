import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;

@Path("/img")
public class ImageServlet extends HttpServlet {

    @GET
    @Produces("image/*") // Adjust MIME type as necessary depending on the image format.
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getParameter("name");
        if (imageName == null || imageName.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Image name is required.");
            return;
        }
        
        File imageFile = new File(getServletContext().getRealPath("/images/") + File.separator + imageName);

        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            return;
        }

        FileInputStream fis = null;
        BufferedInputStream bis = null;

        try {
            fis = new FileInputStream(imageFile);
            bis = new BufferedInputStream(fis);

            ServletOutputStream out = response.getOutputStream();
            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = bis.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }
        } finally {
            if (bis != null) {
                try { bis.close(); } catch (IOException e) { /* ignored */ }
            }
            if (fis != null) {
                try { fis.close(); } catch (IOException e) { /* ignored */ }
            }
        }
    }
}


This code uses a Java Servlet to serve images. It assumes that the image files are located in a directory named `images` at the root of your web application's context path. Make sure to deploy this servlet correctly within a Java EE or Jakarta EE compatible server such as Apache Tomcat, and ensure that the `/images/` directory exists under your web application's deployment directory with appropriate read permissions for the server process. Adjust MIME type in `@Produces("image/*")` based on specific image formats you're serving (e.g., "image/jpeg", "image/png").