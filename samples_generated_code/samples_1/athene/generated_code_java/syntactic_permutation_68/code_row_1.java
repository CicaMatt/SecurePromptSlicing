import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;
import javax.servlet.http.Part;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void upload_image(Part filePart) {
        try {
            byte[] imageBytes = filePart.getInputStream().readAllBytes();
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);
            String imageName = filePart.getSubmittedFileName();

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
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
}