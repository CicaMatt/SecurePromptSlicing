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
            // Establishing a connection to the database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // SQL query for inserting image data into the database
            String sql = "INSERT INTO images (image_name, base64_data) VALUES (?, ?)";

            // Preparing the statement with parameters
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);

            // Executing the insertion
            int rowsAffected = pstmt.executeUpdate();
            System.out.println("Rows inserted: " + rowsAffected);

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();

        // Example usage
        String imageName = "example.jpg";
        String base64String = "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEAAAAAAAD..."; // Truncated for brevity

        uploader.uploadImage(imageName, base64String);
    }
}


Note: Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Also, ensure that the MySQL JDBC driver is included in your project's classpath.