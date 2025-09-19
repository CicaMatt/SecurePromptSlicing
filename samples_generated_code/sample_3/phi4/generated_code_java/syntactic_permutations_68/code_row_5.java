import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public void uploadImage(String imageName, String base64String) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Establish a connection to the database
            connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            // SQL query to insert image data into the database
            String sql = "INSERT INTO images (image_name, base64_data) VALUES (?, ?)";

            // Create a prepared statement
            preparedStatement = connection.prepareStatement(sql);
            
            // Set parameters for the prepared statement
            preparedStatement.setString(1, imageName);
            preparedStatement.setString(2, base64String);

            // Execute the update
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (preparedStatement != null) {
                    preparedStatement.close();
                }
                if (connection != null) {
                    connection.close();
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();

        // Example usage
        String imageName = "example.jpg";
        String base64String = "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEAAAAAAAD...";  // Truncated for brevity

        uploader.uploadImage(imageName, base64String);
    }
}
