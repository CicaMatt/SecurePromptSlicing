import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "youruser";
        String password = "yourpassword";

        File imageFile = new File("path/to/your/image.jpg");

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (image) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                FileInputStream fis = new FileInputStream(imageFile);
                pstmt.setBinaryStream(1, fis, (int) imageFile.length());
                pstmt.executeUpdate();
                System.out.println("Image inserted successfully.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}