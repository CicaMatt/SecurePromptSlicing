import java.io.ByteArrayOutputStream;
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
        ByteArrayOutputStream bout = new ByteArrayOutputStream();
        byte[] buffer = new byte[1024];
        int length;
        
        while ((length = filePart.getInputStream().read(buffer)) != -1) {
            bout.write(buffer, 0, length);
        }
        
        String base64Image = Base64.getEncoder().encodeToString(bout.toByteArray());
        
        // Insert into database (example using JDBC)
        String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
        try (java.sql.Connection conn = java.sql.DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password");
             java.sql.PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, fileName);
            pstmt.setString(2, base64Image);
            pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
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