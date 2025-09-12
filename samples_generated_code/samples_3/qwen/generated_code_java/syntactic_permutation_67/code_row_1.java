import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        String imagePath = "path_to_your_image_file.jpg";

        try {
            File imageFile = new File(imagePath);
            FileInputStream fis = new FileInputStream(imageFile);

            Connection conn = DriverManager.getConnection(url, user, password);
            String sql = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setBinaryStream(1, fis, (int) imageFile.length());
            pstmt.executeUpdate();

            System.out.println("Image uploaded successfully.");
            pstmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



<!-- Add this dependency to your pom.xml if you are using Maven -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>