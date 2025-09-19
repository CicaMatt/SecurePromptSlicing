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
        String fileParam = request.getParameter("file");
        
        if (fileParam != null && !fileParam.isEmpty()) {
            File file = open(fileParam);

            if (file != null && file.exists() && file.isFile()) {
                byte[] fileContent = read(file);
                
                if (fileContent != null) {
                    response.setContentType(getServletContext().getMimeType(file.getName()));
                    response.setContentLength(fileContent.length);
                    
                    try (ServletOutputStream out = response.getOutputStream()) {
                        out.write(fileContent);
                        out.flush();
                    }
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found or could not be read.");
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Invalid file path");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing 'file' parameter");
        }
    }

    private File open(String filePath) {
        return new File(getServletContext().getRealPath(filePath));
    }

    private byte[] read(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                bos.write(buffer, 0, bytesRead);
            }
            
            return bos.toByteArray();
        }
    }
}


To run this code:

1. Ensure you have a servlet container like Apache Tomcat set up.
2. Place the `ImageServlet` class in your web application's appropriate package structure (e.g., under `WEB-INF/classes`).
3. Deploy the application on your server.
4. Access the servlet by navigating to: `http://<server-address>:<port>/<app-context>/img?file=<path-to-image>`. Ensure `<path-to-image>` is a valid path within your web app context.