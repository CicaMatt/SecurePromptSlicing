import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void uploadImage(String imagePath, String imageName) {
        try {
            byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));
            String base64String = Base64.encodeBase64String(imageBytes);

            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
                 PreparedStatement pstmt = conn.prepareStatement("INSERT INTO images (name, data) VALUES (?, ?)")) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64String);
                pstmt.executeUpdate();
            }
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        String imageName = "image_name.jpg";
        uploadImage(imagePath, imageName);
    }
}


Make sure to include the necessary dependencies in your project:

- Apache Commons Codec for Base64 encoding: `commons-codec`
- MySQL JDBC Driver: `mysql-connector-java`

You can add these dependencies using Maven by including them in your `pom.xml`:


<dependency>
    <groupId>commons-codec</groupId>
    <artifactId>commons-codec</artifactId>
    <version>1.15</version>
</dependency>
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.27</version>
</dependency>