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

        String imagePath = "path_to_your_image_file.jpg";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (image) VALUES (?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                File imageFile = new File(imagePath);
                FileInputStream fis = new FileInputStream(imageFile);

                preparedStatement.setBinaryStream(1, fis, (int) imageFile.length());
                preparedStatement.executeUpdate();

                System.out.println("Image uploaded successfully.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



-- SQL to create the table in MySQL before running the Java program
CREATE TABLE images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image BLOB
);