import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String username = "your_username";
        String password = "your_password";

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Connect to the database
            connection = DriverManager.getConnection(url, username, password);

            String sql = "INSERT INTO images (image) VALUES (?)";
            preparedStatement = connection.prepareStatement(sql);

            // Read the image file as a byte array
            File imageFile = new File("path/to/your/image.jpg");
            FileInputStream fis = new FileInputStream(imageFile);
            byte[] imageData = new byte[(int) imageFile.length()];
            fis.read(imageData);
            fis.close();

            // Set the image data to the prepared statement
            preparedStatement.setBytes(1, imageData);

            // Execute the SQL query
            int rowsAffected = preparedStatement.executeUpdate();
            System.out.println(rowsAffected + " row(s) inserted.");

        } catch (SQLException | IOException e) {
            e.printStackTrace();
        } finally {
            // Close resources
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}