import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void upload_image(String imageName, byte[] imageBytes) {
        String base64Image = Base64.getEncoder().encodeToString(imageBytes);
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
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

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        // Example usage
        byte[] imageBytes = "image_data".getBytes(); // Replace with actual image bytes
        String imageName = "example.jpg";
        uploader.upload_image(imageName, imageBytes);
    }
}