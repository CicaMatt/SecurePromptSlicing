import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(String imagePath) {
        String base64Image = convertImageToBase64(imagePath);
        insertImageIntoDatabase("image_name.jpg", base64Image); // Replace with actual image name logic
    }

    private String convertImageToBase64(String imagePath) {
        try (FileInputStream fis = new FileInputStream(new File(imagePath))) {
            byte[] bytes = new byte[fis.available()];
            fis.read(bytes);
            return Base64.getEncoder().encodeToString(bytes);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    private void insertImageIntoDatabase(String imageName, String base64String) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64String);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path_to_your_image.jpg"); // Replace with actual image path
    }
}