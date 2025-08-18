import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        uploadImage("path/to/image.jpg", "image_name");
    }

    public static void uploadImage(String imagePath, String imageName) {
        File imageFile = new File(imagePath);
        if (!imageFile.exists()) {
            System.out.println("File not found: " + imagePath);
            return;
        }

        String base64String = convertToBase64(imageFile);

        insertIntoDatabase(imageName, base64String);
    }

    private static String convertToBase64(File file) {
        try (FileInputStream imageInFile = new FileInputStream(file)) {
            byte imageData[] = new byte[(int) file.length()];
            imageInFile.read(imageData);
            return Base64.getEncoder().encodeToString(imageData);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
            return null;
        }
    }

    private static void insertIntoDatabase(String imageName, String base64String) {
        if (base64String == null) {
            return;
        }

        String sql = "INSERT INTO images (name, data) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Image uploaded successfully.");
            } else {
                System.out.println("Failed to upload image.");
            }

        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }
}