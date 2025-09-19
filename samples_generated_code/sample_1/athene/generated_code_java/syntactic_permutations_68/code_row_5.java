import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void upload_image(String imageName, byte[] imageBytes) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, base64_data) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, imageName);
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);
            statement.setString(2, encodedImage);
            statement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}