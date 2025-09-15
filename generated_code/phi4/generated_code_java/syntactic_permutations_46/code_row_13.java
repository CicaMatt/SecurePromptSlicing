import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getPathInfo();
        if (imageName == null || imageName.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Image name is required");
            return;
        }

        File imageFile = new File(getServletContext().getRealPath("/images") + File.separator + imageName.substring(1));

        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
            return;
        }

        FileInputStream fileInputStream = null;
        try {
            fileInputStream = new FileInputStream(imageFile);
            byte[] buffer = new byte[4096];
            int bytesRead;

            ServletOutputStream servletOutputStream = response.getOutputStream();
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                servletOutputStream.write(buffer, 0, bytesRead);
            }
        } finally {
            if (fileInputStream != null) {
                fileInputStream.close();
            }
        }
    }
}
