import java.io.File;
import java.io.FileInputStream;
import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void upload_image(File imageFile) {
        try (FileInputStream fis = new FileInputStream(imageFile)) {
            byte[] bytes = new byte[(int) imageFile.length()];
            fis.read(bytes);
            String base64Image = Base64.getEncoder().encodeToString(bytes);

            String imageName = imageFile.getName();
            insertIntoDatabase(imageName, base64Image);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void insertIntoDatabase(String name, String base64String) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, name);
            statement.setString(2, base64String);
            statement.executeUpdate();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File file = new File("path/to/your/image.jpg");
        uploader.upload_image(file);
    }
}