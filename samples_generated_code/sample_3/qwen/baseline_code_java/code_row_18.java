import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {
    public static void main(String[] args) {
        String dbURL = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "yourusername";
        String pass = "yourpassword";
        
        String filePath = "path/to/your/image.jpg"; // Specify the path to your image file

        try (FileInputStream fis = new FileInputStream(new File(filePath));
             Connection conn = DriverManager.getConnection(dbURL, user, pass);
             PreparedStatement ps = conn.prepareStatement("INSERT INTO images (image) VALUES (?)")) {

            ps.setBinaryStream(1, fis, (int) new File(filePath).length());
            int rowsInserted = ps.executeUpdate();

            if (rowsInserted > 0) {
                System.out.println("The file has been uploaded successfully!");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}