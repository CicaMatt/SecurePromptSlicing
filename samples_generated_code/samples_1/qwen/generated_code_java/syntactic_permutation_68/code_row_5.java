import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUpload {

    public static void main(String[] args) {
        String imageName = "example.jpg";
        String base64Image = "/9j/4AAQSkZJRgABAQEAAAAAAA...";
        
        uploadImage(imageName, base64Image);
    }

    public static void uploadImage(String imageName, String base64String) {
        String url = "jdbc:mysql://localhost:3306/image_database";
        String user = "root";
        String password = "password";

        String sql = "INSERT INTO images (name, base64_string) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);

            int rowsInserted = pstmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new image was inserted successfully!");
            }

        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}