import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUpload {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(String imageName, String base64String) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, base64_data) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, imageName);
                preparedStatement.setString(2, base64String);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUpload imageUpload = new ImageUpload();
        String imageName = "example.jpg";
        String base64String = "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEASABIAAD...";
        imageUpload.uploadImage(imageName, base64String);
    }
}
