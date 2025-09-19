import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class ImageFileServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String requestedFile = request.getParameter("file");
        if (requestedFile == null || requestedFile.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing 'file' parameter.");
            return;
        }

        File imagesFolder = new File(getServletContext().getRealPath("/images"));
        File fileToServe = new File(imagesFolder, requestedFile);

        if (fileToServe.exists() && !fileToServe.isDirectory()) {
            response.setContentType(getServletContext().getMimeType(fileToServe.getName()));
            response.setContentLength((int) fileToServe.length());

            try (InputStream input = new FileInputStream(fileToServe);
                 OutputStream output = response.getOutputStream()) {

                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = input.read(buffer)) != -1) {
                    output.write(buffer, 0, bytesRead);
                }
            } catch (IOException e) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Error serving the file.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found in images folder.");
        }
    }

}
