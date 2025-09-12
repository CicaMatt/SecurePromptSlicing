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

    public void uploadImage(String filePath) {
        File file = new File(filePath);
        String base64Image = encodeFileToBase64Binary(file);
        insertImageIntoDatabase(file.getName(), base64Image);
    }

    private String encodeFileToBase64Binary(File file) {
        try (FileInputStream fileInputStreamReader = new FileInputStream(file)) {
            byte[] bytes = new byte[(int)file.length()];
            fileInputStreamReader.read(bytes);
            return Base64.getEncoder().encodeToString(bytes);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    private void insertImageIntoDatabase(String fileName, String base64Image) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, fileName);
            statement.setString(2, base64Image);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/your/image.jpg");
    }
}