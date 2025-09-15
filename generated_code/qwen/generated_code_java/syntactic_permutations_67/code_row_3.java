import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";
        String imagePath = "path_to_your_image.jpg";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             FileInputStream inputStream = new FileInputStream(new File(imagePath));
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO images (image) VALUES (?)")) {

            preparedStatement.setBinaryStream(1, inputStream);
            preparedStatement.executeUpdate();
            System.out.println("Image uploaded successfully!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
