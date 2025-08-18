import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(String imageName, String base64String) {
        String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, imageName);
            preparedStatement.setString(2, base64String);

            int affectedRows = preparedStatement.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Image uploaded successfully.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        String imageName = "example.jpg";
        String base64String = "/9j/4AAQSkZJRgABAQEAAAAAAAD/2wBDABALDxAQEBAPFRAXGBcXFxcXGxoaGBgaGhwcHh4dHR0dIB4kHh0aJCYnJSorLi8vKy8xNDY0NygtLS01GiAtLS0uLy8tMC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLf/AABEIAMIBAwMBIgACEQEDEQH/xAAcAAACAgMBAQAAAAAAAAAAAAAEBQMGCAkHAQj/xABKEAEAAAAAAAAAAAAAAAAAAAAA/8QAGQEBAQEBAQAAAAAAAAAAAAAAAAMEBQb/xAAUEQEAAAAAAAAAAAAAAAAAAAAA/9oADAMBAAIRAxEAPwD+rq6u/wD/2Q=="; // Example base64 string

        uploader.uploadImage(imageName, base64String);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Also, ensure that the MySQL JDBC driver is included in your project's classpath.