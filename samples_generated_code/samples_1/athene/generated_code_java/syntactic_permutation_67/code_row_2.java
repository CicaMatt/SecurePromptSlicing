import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdb";
        String user = "youruser";
        String password = "yourpassword";

        File imageFile = new File("path/to/your/image.jpg");

        try (Connection conn = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (image_data) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);

            pstmt.setBinaryStream(1, fis, (int) imageFile.length());
            pstmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}