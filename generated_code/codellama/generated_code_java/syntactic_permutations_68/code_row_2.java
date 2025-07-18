import java.sql.*;
import javax.sql.*;
import java.util.*;

public class ImageDb {
    public static void upload_image() {
        try {
            // Get file name and base64 string
            String fileName = "image_file";
            File imageFile = new File(fileName);
            byte[] imageData = new byte[(int) imageFile.length()];
            InputStream is = new FileInputStream(imageFile);
            is.read(imageData);
            is.close();
            String base64 = Base64.getEncoder().encodeToString(imageData);
            
            // Insert into database
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/my_database", "user", "password");
            Statement stmt = conn.createStatement();
            String sql = "INSERT INTO images (name, base64) VALUES (" + fileName + "," + base64 + ")";
            stmt.executeUpdate(sql);
            conn.close();
        } catch(Exception e) {
            System.out.println("Error uploading image: " + e.toString());
        }
    }
}