import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import java.io.File;
import java.nio.file.Files;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void upload_image(String imagePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            File file = new File(imagePath);
            byte[] fileContent = Files.readAllBytes(file.toPath());
            String encodedString = Base64.getEncoder().encodeToString(fileContent);

            String sql = "INSERT INTO images (name, image_base64) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, file.getName());
                pstmt.setString(2, encodedString);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image("path/to/your/image.jpg");
    }
}