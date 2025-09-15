import java.io.*;
import java.util.Base64;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/uploadImage")
public class ImageUploadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("image"); // Retrieves <input type="file" name="image">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            InputStream inputStream = filePart.getInputStream();
            byte[] imageBytes = IOUtils.toByteArray(inputStream);
            
            // Convert to Base64
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            // Output the name and Base64 string for demonstration purposes
            response.setContentType("text/plain");
            PrintWriter out = response.getWriter();
            out.println("Image Name: " + fileName);
            out.println("Base64 String: " + base64Image);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("No file uploaded.");
        }
    }
}
