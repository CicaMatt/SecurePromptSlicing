import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.io.FileInputStream;
import java.io.File;

public class ImageUploader {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdb";
        String user = "username";
        String password = "password";

        File imageFile = new File("path/to/image.jpg");
        
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO images (image) VALUES (?)")) {
            
            FileInputStream fis = new FileInputStream(imageFile);
            pstmt.setBinaryStream(1, fis, (int) imageFile.length());
            pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}