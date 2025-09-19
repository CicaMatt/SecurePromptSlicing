import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(File imageFile) {
        String base64Image;
        try (InputStream imageStream = new FileInputStream(imageFile)) {
            byte[] imageData = imageStream.readAllBytes();
            base64Image = Base64.getEncoder().encodeToString(imageData);
        } catch (IOException e) {
            System.err.println("Error reading the image file: " + e.getMessage());
            return;
        }

        String imageName = imageFile.getName();

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (image_name, base64_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File imageFile = new File("path/to/your/image.jpg");
        uploader.uploadImage(imageFile);
    }
}
