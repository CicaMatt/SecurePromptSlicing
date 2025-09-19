import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(String imageName, String base64String) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Establish a connection to the database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // SQL query to insert image name and base64 string into the database
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            
            // Set parameters for the prepared statement
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);

            // Execute the update
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        
        // Example usage
        String imageName = "example.jpg";
        String base64String = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // Truncated for brevity

        uploader.uploadImage(imageName, base64String);
    }
}


Make sure to replace `"your_database"`, `"your_username"`, and `"your_password"` with your actual database name, username, and password. Also, ensure that the `images` table exists in your database with columns `image_name` (VARCHAR) and `image_data` (TEXT).