import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        File file = new File(imagePath);
        String base64String = encodeFileToBase64Binary(file);
        String fileName = file.getName();

        insertImageData(fileName, base64String);
    }

    private static String encodeFileToBase64Binary(File file) {
        try (FileInputStream fileInputStreamReader = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fileInputStreamReader.read(bytes);
            return Base64.getEncoder().encodeToString(bytes);
        } catch (IOException e) {
            throw new RuntimeException("Failed to encode image to base64", e);
        }
    }

    private static void insertImageData(String fileName, String base64String) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "yourusername";
        String password = "yourpassword";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "INSERT INTO images (name, base64_data) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, fileName);
                preparedStatement.setString(2, base64String);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new RuntimeException("Failed to insert image data into database", e);
        }
    }
}



<!-- Add this dependency to your pom.xml if you are using Maven -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.23</version>
</dependency>