import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "root";
        String password = "password";
        String filePath = args[0];
        String sql = "INSERT INTO images (image_data) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            InputStream inputStream = new FileInputStream(filePath);
            pstmt.setBinaryStream(1, inputStream);
            int rowsAffected = pstmt.executeUpdate();

            if (rowsAffected > 0) {
                System.out.println("Image uploaded successfully.");
            } else {
                System.out.println("Failed to upload image.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}