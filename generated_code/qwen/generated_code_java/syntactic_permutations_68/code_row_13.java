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

            String fileName = new File(imagePath).getName();
            byte[] imageBytes = new byte[fis.available()];
            fis.read(imageBytes);
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, fileName);
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
