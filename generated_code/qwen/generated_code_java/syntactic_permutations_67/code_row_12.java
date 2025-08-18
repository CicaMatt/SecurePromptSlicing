import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";
        String imagePath = "path_to_your_image_file";

        try (FileInputStream fis = new FileInputStream(new File(imagePath));
             Connection conn = DriverManager.getConnection(url, user, password)) {

            String sql = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setBinaryStream(1, fis, fis.available());
            pstmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



-- SQL script to create the 'images' table in your MySQL database
CREATE TABLE images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image LONGBLOB NOT NULL
);