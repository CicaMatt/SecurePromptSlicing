import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String imagePath = "path_to_your_image.jpg";
        File imageFile = new File(imagePath);

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            FileInputStream inputStream = new FileInputStream(imageFile);
            preparedStatement.setBinaryStream(1, inputStream, (int) imageFile.length());
            preparedStatement.executeUpdate();
            System.out.println("Image uploaded successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
