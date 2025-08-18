import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold=1024*1024*2, // 2MB
                 maxFileSize=1024*1024*10,      // 10MB
                 maxRequestSize=1024*1024*50)   // 50MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        for (Part part : request.getParts()) {
            part.write(getServletContext().getRealPath("") + File.separator + fileName);
        }
        response.getWriter().println("File " + fileName + " has uploaded successfully!");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().print("<html><body>");
        response.getWriter().print("<form action='upload' method='post' enctype='multipart/form-data'>");
        response.getWriter().print("<p>Select a file : <input type='file' name='file' size='60'/></p>");
        response.getWriter().print("<input type='submit' value='Upload' /></p>");
        response.getWriter().print("</form>");
        response.getWriter().println("</body></html>");
    }
}