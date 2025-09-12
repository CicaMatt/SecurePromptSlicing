import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            File file = new File(imagePath);
            String fileName = file.getName();
            byte[] fileContent = new byte[(int) file.length()];

            try (FileInputStream fis = new FileInputStream(file)) {
                fis.read(fileContent);
            }

            String base64Image = Base64.getEncoder().encodeToString(fileContent);

            String sql = "INSERT INTO images (name, content) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, fileName);
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



<!-- pom.xml if using Maven for MySQL JDBC dependency -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>