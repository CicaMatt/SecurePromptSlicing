import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";
    private static final String INSERT_QUERY = "INSERT INTO images (name, data) VALUES (?, ?)";

    public void upload_image(String imageName, byte[] imageData) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(INSERT_QUERY)) {

            String base64Image = Base64.getEncoder().encodeToString(imageData);
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64Image);
            pstmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        // Example usage
        byte[] exampleImageData = "example image data".getBytes();
        uploader.upload_image("example.jpg", exampleImageData);
    }
}