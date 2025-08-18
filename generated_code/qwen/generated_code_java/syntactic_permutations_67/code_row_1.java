import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String user = "root";
        String password = "password";

        String imagePath = "path/to/your/image.jpg";
        File imageFile = new File(imagePath);

        try (Connection connection = DriverManager.getConnection(url, user, password);
             FileInputStream inputStream = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (image_data) VALUES (?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setBinaryStream(1, inputStream, (int) imageFile.length());
            preparedStatement.executeUpdate();

            System.out.println("Image uploaded successfully!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}