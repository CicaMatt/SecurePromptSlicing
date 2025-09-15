import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        String imagePath = "path_to_your_image_file.jpg";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(new File(imagePath));
             PreparedStatement ps = conn.prepareStatement("INSERT INTO images (image) VALUES (?)")) {

            ps.setBinaryStream(1, fis, (int) new File(imagePath).length());
            ps.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
