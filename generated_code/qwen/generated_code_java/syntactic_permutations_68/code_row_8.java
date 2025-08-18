import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (FileInputStream fileInputStream = new FileInputStream(new File(imagePath));
             Connection connection = DriverManager.getConnection(url, user, password)) {

            byte[] imageBytes = new byte[fileInputStream.available()];
            fileInputStream.read(imageBytes);

            String base64Image = Base64.getEncoder().encodeToString(imageBytes);
            String imageName = new File(imagePath).getName();

            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, imageName);
                preparedStatement.setString(2, base64Image);
                preparedStatement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



<!-- Add this dependency to your pom.xml if you are using Maven -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.23</version>
</dependency>