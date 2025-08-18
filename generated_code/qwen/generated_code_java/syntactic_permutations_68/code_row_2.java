import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Replace with the actual image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String filePath) {
        File file = new File(filePath);
        String base64Image = encodeFileToBase64Binary(file);

        if (base64Image != null) {
            String fileName = file.getName();
            insertImageIntoDatabase(fileName, base64Image);
        }
    }

    private static String encodeFileToBase64Binary(File file) {
        try (FileInputStream fileInputStreamReader = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fileInputStreamReader.read(bytes);
            return Base64.getEncoder().encodeToString(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    private static void insertImageIntoDatabase(String fileName, String base64Image) {
        String url = "jdbc:mysql://localhost:3306/your_database"; // Replace with your database URL
        String user = "your_username"; // Replace with your database username
        String password = "your_password"; // Replace with your database password

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "INSERT INTO images (name, data) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, fileName);
                preparedStatement.setString(2, base64Image);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `"path/to/your/image.jpg"`, `"jdbc:mysql://localhost:3306/your_database"`, `"your_username"`, and `"your_password"` with the actual file path, database URL, username, and password. Also, ensure that your database has a table named `images` with columns `name` (VARCHAR) and `data` (TEXT or similar type to store base64 strings).