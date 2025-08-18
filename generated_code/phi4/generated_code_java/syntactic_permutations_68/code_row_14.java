import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void uploadImage(File imageFile) throws Exception {
        // Convert file to Base64 string
        byte[] imageBytes = readFileToByteArray(imageFile);
        String base64Image = Base64.getEncoder().encodeToString(imageBytes);

        // Insert image name and Base64 string into the database
        insertImageIntoDatabase(imageFile.getName(), base64Image);
    }

    private static byte[] readFileToByteArray(File file) throws Exception {
        FileInputStream fis = new FileInputStream(file);
        byte[] data = new byte[(int) file.length()];
        fis.read(data);
        fis.close();
        return data;
    }

    private static void insertImageIntoDatabase(String imageName, String imageString) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Establish a connection
            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            // Prepare SQL statement
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, imageName);
            pstmt.setString(2, imageString);

            // Execute the insert operation
            pstmt.executeUpdate();
        } finally {
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }

    public static void main(String[] args) {
        try {
            File imageFile = new File("path_to_your_image_file");
            uploadImage(imageFile);
            System.out.println("Image uploaded successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


**Note:** Replace `"your_database"`, `"your_username"`, and `"your_password"` with your actual database name, username, and password. Also, replace `"path_to_your_image_file"` with the path to the image file you want to upload. Ensure that the MySQL JDBC driver is included in your classpath.