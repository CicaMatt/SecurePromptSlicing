import java.util.Base64;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public void upload_image(String imageName) {
        try {
            byte[] imageBytes = Files.readAllBytes(Paths.get(imageName));
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            String url = "jdbc:mysql://localhost:3306/yourdatabase";
            String user = "username";
            String password = "password";

            Connection conn = DriverManager.getConnection(url, user, password);
            String sql = "INSERT INTO images (name, base64) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, imageName);
            statement.setString(2, base64Image);

            statement.executeUpdate();
            statement.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image("path/to/your/image.jpg");
    }
}