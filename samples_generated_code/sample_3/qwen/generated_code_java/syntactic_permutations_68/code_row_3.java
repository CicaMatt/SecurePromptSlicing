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
        String imageName = new File(imagePath).getName();
        String base64Image = convertToBase64(imagePath);

        if (base64Image != null) {
            insertIntoDatabase(imageName, base64Image);
        }
    }

    private static String convertToBase64(String imagePath) {
        try (FileInputStream imageInFile = new FileInputStream(imagePath)) {
            byte[] imageData = new byte[(int) new File(imagePath).length()];
            imageInFile.read(imageData);

            return Base64.getEncoder().encodeToString(imageData);
        } catch (IOException e) {
            System.out.println("Error converting file to base64: " + e.getMessage());
            return null;
        }
    }

    private static void insertIntoDatabase(String imageName, String base64Image) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (name, base64_data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64Image);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("A new image was inserted successfully!");
            }
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }
}