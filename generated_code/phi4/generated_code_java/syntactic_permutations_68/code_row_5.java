import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void uploadImage(File imageFile, String imageName) {
        byte[] imageData;
        try (FileInputStream fis = new FileInputStream(imageFile)) {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int length;

            while ((length = fis.read(buffer)) != -1) {
                baos.write(buffer, 0, length);
            }

            imageData = baos.toByteArray();

        } catch (IOException e) {
            throw new RuntimeException("Error reading image file", e);
        }

        String base64Image = Base64.getEncoder().encodeToString(imageData);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error inserting data into database", e);
        }
    }

    public static void main(String[] args) {
        File imageFile = new File("path/to/your/image.jpg");
        String imageName = "image.jpg";
        uploadImage(imageFile, imageName);
    }
}
