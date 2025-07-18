import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(location = "/uploads")  // Configure the location to save uploaded files 
public class UploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    // Define a method to handle file upload requests
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        for (Part part : request.getParts()) {
            String fileName = new File(part.getName()).getName();  // Get uploaded file name
            part.write("/uploads/" + fileName);                    // Write the uploaded file to a specified folder on the server
            response.sendRedirect("uploads/" + fileName);          // Redirect user to the uploaded file
        }
    }
}