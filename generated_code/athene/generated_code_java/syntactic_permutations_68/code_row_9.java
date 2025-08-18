import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.imageio.ImageIO;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void upload_image(HttpServletRequest request) throws ServletException, IOException {
        try {
            // Read the image from the request
            byte[] imageData = request.getPart("image").getInputStream().readAllBytes();
            
            // Convert the image to base64
            String base64Image = Base64.getEncoder().encodeToString(imageData);

            // Get the image name
            String imageName = request.getPart("image").getSubmittedFileName();

            // Insert into database
            insertIntoDatabase(imageName, base64Image);
        } catch (Exception e) {
            throw new ServletException("Error uploading image", e);
        }
    }

    private void insertIntoDatabase(String imageName, String base64Image) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, image_base64) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        }
    }
}