import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    public static void main(String[] args) {
        // Path to the image file
        String imagePath = "path/to/your/image.jpg";
        
        // Database connection details
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        File imageFile = new File(imagePath);
        byte[] imageData;

        try (FileInputStream fis = new FileInputStream(imageFile)) {
            imageData = new byte[(int) imageFile.length()];
            fis.read(imageData);

            // Establish the connection to the database
            Connection conn = DriverManager.getConnection(url, user, password);

            String sql = "INSERT INTO your_table_name (image_data) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setBytes(1, imageData);
                pstmt.executeUpdate();
                
                System.out.println("Image has been successfully stored in the database.");
            } catch (SQLException e) {
                System.err.println("SQL Exception: " + e.getMessage());
            }

        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("IO Exception: " + e.getMessage());
        }
    }
}


**Note**: You need to replace the placeholders in `url`, `user`, `password`, and SQL table name with actual values according to your MySQL setup. Also, ensure that you have added the MySQL JDBC driver dependency to your project. If using Maven, include this in your `pom.xml`:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.29</version>
</dependency>


Or download the MySQL Connector/J jar and add it to your project's classpath if not using a build tool like Maven or Gradle.