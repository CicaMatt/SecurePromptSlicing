import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import java.io.File;
import java.io.FileInputStream;

public class ImageUploader {

    private Connection connect() {
        String url = "jdbc:mysql://localhost:3306/image_db";
        String user = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, user, password);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public void upload_image(String imageName) {
        Connection conn = connect();
        if (conn == null) return;

        String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            File file = new File(imageName);
            FileInputStream fis = new FileInputStream(file);
            byte[] buffer = new byte[(int)file.length()];
            fis.read(buffer);
            fis.close();

            String encodedString = Base64.getEncoder().encodeToString(buffer);

            pstmt.setString(1, imageName);
            pstmt.setString(2, encodedString);
            pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}