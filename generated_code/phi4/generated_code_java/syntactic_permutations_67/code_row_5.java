import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageToDatabase <imageFilePath>");
            return;
        }

        String imageFilePath = args[0];
        File imageFile = new File(imageFilePath);
        
        if (!imageFile.exists()) {
            System.out.println("Image file does not exist.");
            return;
        }
        
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String query = "INSERT INTO images_table (image_name, image_data) VALUES (?, ?)";
            
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                
                FileInputStream inputStream = new FileInputStream(imageFile);
                
                preparedStatement.setString(1, imageFile.getName());
                preparedStatement.setBinaryStream(2, inputStream, (int) imageFile.length());

                int rowsInserted = preparedStatement.executeUpdate();
                
                if (rowsInserted > 0) {
                    System.out.println("Image saved successfully.");
                }
            }

        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}


**Note:** Make sure to replace `"your_database"`, `"username"`, and `"password"` with your actual MySQL database name, username, and password. The table `images_table` should have columns `image_name` as VARCHAR or TEXT and `image_data` as BLOB. Ensure the MySQL JDBC driver is included in your classpath.