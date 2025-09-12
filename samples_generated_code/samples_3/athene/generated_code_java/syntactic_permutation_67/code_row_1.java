import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "yourusername";
        String password = "yourpassword";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (image_data) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                FileInputStream fis = new FileInputStream("path/to/your/image.jpg");
                pstmt.setBinaryStream(1, fis);
                pstmt.executeUpdate();
                System.out.println("Image inserted successfully.");
            } catch (IOException e) {
                e.printStackTrace();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}