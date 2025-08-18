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
        String imagePath = "path_to_your_image_file";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            File file = new File(imagePath);
            FileInputStream fis = new FileInputStream(file);

            String query = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setBinaryStream(1, fis, (int) file.length());

            preparedStatement.executeUpdate();
            System.out.println("File uploaded successfully!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}