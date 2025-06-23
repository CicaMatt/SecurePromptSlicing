import java.io.File;  
import javax.servlet.*;  
import javax.servlet.http.*;

public class UploadServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get the file chosen by the user.
        Part part = request.getPart("file");
        String filename = getFilename(part);

        // Write the file to the server.
        File uploads = new File("/path/to/uploads/directory");
        if (!uploads.exists()) {
            uploads.mkdir();
        }
        part.write(filename);
    }  

    private String getFilename(Part part) {
        // Get the name of the uploaded file.
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }  
}