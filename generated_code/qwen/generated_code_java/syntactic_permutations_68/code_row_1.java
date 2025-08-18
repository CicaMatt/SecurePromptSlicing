import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/image.jpg"; // Replace with the actual image path
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
            throw new RuntimeException("Error encoding file to base64", e);
        }
    }

    private static void insertImageData(String fileName, String base64String) {
        String url = "jdbc:mysql://localhost:3306/your_database"; // Replace with your database URL
        String user = "your_username"; // Replace with your database username
        String password = "your_password"; // Replace with your database password

        String sql = "INSERT INTO images (name, data) VALUES (?, ?)";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, fileName);
            preparedStatement.setString(2, base64String);

            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Image inserted successfully.");
            }

        } catch (Exception e) {
            throw new RuntimeException("Error inserting image data into database", e);
        }
    }
}