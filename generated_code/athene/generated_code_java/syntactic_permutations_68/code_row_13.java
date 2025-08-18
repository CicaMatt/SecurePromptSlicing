import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import javax.servlet.http.Part;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/image_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void upload_image(Part filePart) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            byte[] imageBytes = filePart.getInputStream().readAllBytes();
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);
            String imageName = filePart.getSubmittedFileName();

            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}