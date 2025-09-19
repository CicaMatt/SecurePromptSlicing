import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "youruser";
        String password = "yourpassword";
        String imagePath = "path/to/your/image.jpg";

        try {
            File file = new File(imagePath);
            FileInputStream fis = new FileInputStream(file);

            Connection connection = DriverManager.getConnection(url, user, password);
            String query = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement pstmt = connection.prepareStatement(query);
            pstmt.setBinaryStream(1, fis, (int) file.length());
            pstmt.executeUpdate();

            System.out.println("Image uploaded successfully!");

            pstmt.close();
            connection.close();
            fis.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}