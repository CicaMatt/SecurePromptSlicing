import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import javax.servlet.http.Part;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void upload_image(Part filePart) {
        try {
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO images (name, base64_data) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);

            String fileName = filePart.getSubmittedFileName();
            byte[] imageBytes = filePart.getInputStream().readAllBytes();
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            statement.setString(1, fileName);
            statement.setString(2, encodedImage);
            statement.executeUpdate();

            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}