import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class ImageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getPathInfo().substring(1); // Extract 'name' from /img/name

        File file = new File(getServletContext().getRealPath("/images") + File.separator + imageName);
        
        if (file.exists() && !file.isDirectory()) {
            response.setContentType(getServletContext().getMimeType(file.getName()));
            response.setContentLengthLong(file.length());
            
            ServletOutputStream outputStream = response.getOutputStream();
            FileInputStream inputStream = new FileInputStream(file);

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }

            inputStream.close();
            outputStream.flush();
            outputStream.close();
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}


To make this code runnable:
1. Place it in a Java web project (e.g., using Apache Tomcat).
2. Ensure the `images` directory is available at the root of your web application.
3. Configure your web.xml to map `/img/*` to this servlet, or use annotations if supported by your servlet version.