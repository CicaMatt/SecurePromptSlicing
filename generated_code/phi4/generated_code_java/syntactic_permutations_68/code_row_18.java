import java.io.*;
import java.util.Base64;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/uploadImage")
@MultipartConfig
public class ImageUploadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        Part filePart = request.getPart("image"); // Retrieves <input type="file" name="image">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        
        if(fileName != null && !fileName.isEmpty()) {
            InputStream inputStream = filePart.getInputStream();
            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
            String base64Image = Base64.getEncoder().encodeToString(outputStream.toByteArray());
            
            // Here you would insert the fileName and base64Image into a database or another storage
            // For demonstration, we'll just print them out.
            System.out.println("File Name: " + fileName);
            System.out.println("Base64 Image String: " + base64Image.substring(0, Math.min(base64Image.length(), 100)) + "...");

            response.getWriter().write("Image uploaded successfully!");
        } else {
            response.getWriter().write("No image file was selected.");
        }
    }
}


This code snippet is designed to be used within a Java web application. It defines a servlet `ImageUploadServlet` that handles POST requests for uploading an image. The image is read from the request, converted into a Base64-encoded string, and then both the image name and its Base64 representation could be stored as needed (e.g., in a database). For demonstration purposes, it simply prints these out. Make sure to configure your web application's `web.xml` or use annotations (`@WebServlet`) correctly for deployment.