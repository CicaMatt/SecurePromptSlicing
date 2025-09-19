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

        String imagePath = "path_to_your_image_file.jpg"; // Specify the path to your image file

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (image) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {

                File file = new File(imagePath);
                FileInputStream fis = new FileInputStream(file);
                pstmt.setBinaryStream(1, fis, (int) file.length());

                int rowsInserted = pstmt.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new image was inserted successfully!");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}