import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(String imagePath) {
        try (FileInputStream fis = new FileInputStream(new File(imagePath));
             Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Convert image to Base64
            byte[] bytes = new byte[(int) new File(imagePath).length()];
            fis.read(bytes);
            String base64Image = Base64.getEncoder().encodeToString(bytes);

            // Prepare SQL statement
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, new File(imagePath).getName());
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/your/image.jpg");
    }
}
