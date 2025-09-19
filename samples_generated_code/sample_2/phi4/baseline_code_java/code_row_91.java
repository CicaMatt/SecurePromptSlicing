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

    public void uploadImage(String imagePath, String imageName) {
        try (InputStream imageStream = new FileInputStream(imagePath)) {
            byte[] imageData = imageStream.readAllBytes();
            String base64String = Base64.getEncoder().encodeToString(imageData);

            insertIntoDatabase(imageName, base64String);
        } catch (IOException e) {
            System.err.println("Error reading the image file: " + e.getMessage());
        }
    }

    private void insertIntoDatabase(String imageName, String base64String) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64String);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/your/image.jpg", "image_name.jpg");
    }
}