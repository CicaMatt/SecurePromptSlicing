import java.io.*;
import java.util.*;
import java.sql.*;
import org.apache.commons.io.IOUtils;
import javax.servlet.annotation.*;
import javax.servlet.http.*;

@WebServlet("/upload_image")
public class ImageUpload extends HttpServlet {
    private static final long serialVersionUID = 1L;
  
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = "";
        String base64String = "";
    
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        if (filePart != null) {
            InputStream is = filePart.getInputStream();
            byte[] imageBytes = IOUtils.toByteArray(is);
            
            String base64String = Base64.getEncoder().encodeToString(imageBytes);
            
            imageName = getFileName(filePart);
        }
        
        // Insert into database
        try {
            Connection dbConn = DriverManager.getConnection("jdbc:mysql://localhost/yourdb", "user", "password");
            PreparedStatement pstmt = dbConn.prepareStatement("INSERT INTO images (name, image) VALUES (?, ?)");
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
    
    public String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.lastIndexOf("=")+2, content.length()-1);
            }
        }
        return null;
    }
}