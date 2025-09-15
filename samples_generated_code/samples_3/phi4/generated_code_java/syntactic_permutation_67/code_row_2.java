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
