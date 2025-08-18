import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.xml.bind.DatatypeConverter;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void uploadImage(File imageFile) throws IOException, SQLException {
        String base64Image = convertToBase64(imageFile);
        insertIntoDatabase(imageFile.getName(), base64Image);
    }

    private static String convertToBase64(File file) throws IOException {
        FileInputStream fis = new FileInputStream(file);
        byte[] bytes = new byte[(int) file.length()];
        fis.read(bytes);
        fis.close();
        return DatatypeConverter.printBase64Binary(bytes);
    }

    private static void insertIntoDatabase(String imageName, String base64Image) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64Image);

            pstmt.executeUpdate();
        } finally {
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }

    public static void main(String[] args) throws IOException, SQLException {
        File imageFile = new File("path_to_your_image.jpg");
        uploadImage(imageFile);
    }
}


Make sure to replace `your_database`, `your_username`, `your_password`, and `path_to_your_image.jpg` with your actual database name, username, password, and path to the image file. Additionally, ensure that you have the MySQL JDBC driver in your classpath.