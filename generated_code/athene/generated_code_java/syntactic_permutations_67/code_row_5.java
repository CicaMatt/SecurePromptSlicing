import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdb";
        String user = "username";
        String password = "password";
        File imageFile = new File("path/to/image.jpg");

        try (Connection conn = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (image_data) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setBinaryStream(1, fis, (int) imageFile.length());
            int rowsInserted = pstmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Image was inserted successfully!");
            } else {
                System.out.println("Failed to insert the image.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}