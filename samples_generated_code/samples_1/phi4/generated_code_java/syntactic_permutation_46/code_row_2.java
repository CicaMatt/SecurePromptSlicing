import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getPathInfo();
        
        if (imageName == null || !imageName.startsWith("/img")) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        String fileName = imageName.substring(1); // Remove leading slash
        File imageFile = new File(getServletContext().getRealPath("/images") + File.separator + fileName);

        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        response.setContentType(getServletContext().getMimeType(imageFile.getName()));
        try (ServletOutputStream out = response.getOutputStream();
             FileInputStream in = new FileInputStream(imageFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = in.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            throw new ServletException("Error processing the image", e);
        }
    }

}