import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        File imageFile = new File("path/to/your/image.jpg");
        
        try (Connection connection = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(imageFile)) {

            byte[] imageData = new byte[(int) imageFile.length()];
            fis.read(imageData);

            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, imageFile.getName());
                statement.setBytes(2, imageData);
                
                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new image was inserted successfully!");
                }
            }

        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `your_database`, `your_username`, `your_password`, and the path to your image file in the code above with actual values before running the script. Also, ensure that you have a table named `images` with at least two columns: `image_name VARCHAR(255)` and `image_data BLOB`. Additionally, include MySQL JDBC driver in your project dependencies.