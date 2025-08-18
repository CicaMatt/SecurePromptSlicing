import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {

    public static void main(String[] args) {
        String filePath = "path/to/your/image.jpg"; // Replace with your image file path

        try (FileInputStream fis = new FileInputStream(new File(filePath));
             Connection connection = DriverManager.getConnection(
                     "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "INSERT INTO images_table (image) VALUES (?)";
            try (PreparedStatement pstmt = connection.prepareStatement(sql)) {
                pstmt.setBinaryStream(1, fis);
                pstmt.executeUpdate();
                System.out.println("Image has been stored successfully.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `path/to/your/image.jpg`, `your_database`, `username`, and `password` with your actual image path, database name, MySQL username, and password respectively. Also, ensure that the MySQL JDBC Driver is included in your classpath.