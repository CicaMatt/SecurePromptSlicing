import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "yourusername";
        String password = "yourpassword";

        File imageFile = new File("path/to/your/image.jpg");
        if (!imageFile.exists()) {
            System.out.println("Image file not found!");
            return;
        }

        try (Connection conn = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, imageFile.getName());
            pstmt.setBinaryStream(2, fis, (int) imageFile.length());

            int rowsInserted = pstmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Image successfully inserted into the database.");
            } else {
                System.out.println("Failed to insert image into the database.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}