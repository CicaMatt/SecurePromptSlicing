import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        String imagePath = "path_to_your_image_file.jpg"; // Update with your image path
        File file = new File(imagePath);

        try (FileInputStream fis = new FileInputStream(file);
             Connection conn = DriverManager.getConnection(url, user, password)) {

            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, file.getName());
            pstmt.setBinaryStream(2, fis, (int) file.length());

            int rowsInserted = pstmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("The file has been uploaded successfully!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
