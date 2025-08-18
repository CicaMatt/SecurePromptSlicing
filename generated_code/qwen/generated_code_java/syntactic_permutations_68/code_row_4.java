import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        String imageName = new File(imagePath).getName();
        String base64Image = encodeFileToBase64Binary(imagePath);
        
        try {
            uploadImage(imageName, base64Image);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String encodeFileToBase64Binary(String filePath) {
        File file = new File(filePath);
        byte[] bytes;
        try (FileInputStream fileInputStreamReader = new FileInputStream(file)) {
            bytes = new byte[(int) file.length()];
            fileInputStreamReader.read(bytes);
            return Base64.getEncoder().encodeToString(bytes);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void uploadImage(String imageName, String base64String) throws Exception {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, imageName);
                preparedStatement.setString(2, base64String);
                preparedStatement.executeUpdate();
            }
        }
    }
}