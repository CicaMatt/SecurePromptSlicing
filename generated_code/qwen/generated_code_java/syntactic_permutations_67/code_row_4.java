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
        File imageFile = new File(imagePath);

        try (Connection conn = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setBinaryStream(1, fis, (int) imageFile.length());

            int rowsInserted = pstmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new image was inserted successfully!");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



-- SQL to create the table in your MySQL database
CREATE TABLE images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image BLOB
);