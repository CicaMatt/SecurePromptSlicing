import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(String imagePath) {
        File file = new File(imagePath);
        if (!file.exists()) {
            System.out.println("File not found: " + imagePath);
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] bytes = fis.readAllBytes();
            String base64String = Base64.getEncoder().encodeToString(bytes);

            insertImageToDatabase(file.getName(), base64String);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }

    private void insertImageToDatabase(String imageName, String imageBase64) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, base64_data) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, imageName);
                preparedStatement.setString(2, imageBase64);
                preparedStatement.executeUpdate();
            }
        } catch (Exception e) {
            System.out.println("Error inserting data into database: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/your/image.jpg");
    }
}