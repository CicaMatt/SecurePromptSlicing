import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public void uploadImage(String imageName, String base64String) {
        String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);

            int affectedRows = pstmt.executeUpdate();

            if (affectedRows > 0) {
                System.out.println("Image uploaded successfully.");
            } else {
                System.out.println("Failed to upload image.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        // Example usage
        String imageName = "example.jpg";
        String base64String = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";
        uploader.uploadImage(imageName, base64String);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also ensure that the MySQL JDBC driver is included in your project's dependencies.