import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String imagePath = "path_to_your_image_file.jpg";
        String query = "INSERT INTO images (image_data) VALUES (?)";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             FileInputStream inputStream = new FileInputStream(new File(imagePath));
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setBinaryStream(1, inputStream, (int) new File(imagePath).length());
            preparedStatement.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}