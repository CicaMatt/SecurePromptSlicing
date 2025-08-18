import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "username";
    private static final String PASS = "password";
    private static final String INSERT_QUERY = "INSERT INTO images (name, base64_string) VALUES (?, ?)";

    public void upload_image(String imageName, String base64String) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(INSERT_QUERY)) {

            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);

            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        // Example usage
        uploader.upload_image("example.jpg", "base64EncodedImageStringHere");
    }
}