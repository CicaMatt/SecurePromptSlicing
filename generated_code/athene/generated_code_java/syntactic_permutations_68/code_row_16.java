import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Base64;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload_image")
@MultipartConfig
public class ImageUploadServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("image");
        String fileName = getFileName(filePart);
        
        try (var is = filePart.getInputStream()) {
            byte[] imageBytes = is.readAllBytes();
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            // Assuming you want to send the name and base64 string as a response
            response.setContentType("application/json");
            response.getWriter().write("{\"name\": \"" + fileName + "\", \"base64\": \"" + base64Image + "\"}");
        }
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}