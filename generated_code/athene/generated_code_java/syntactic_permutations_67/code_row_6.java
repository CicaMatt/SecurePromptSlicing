import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.io.File;
import java.io.FileInputStream;

public class ImageToDatabase {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "root";
        String password = "password";

        File file = new File("path/to/your/image.jpg");
        try (Connection conn = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(file)) {

            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, file.getName());
            statement.setBinaryStream(2, fis, (int) file.length());

            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new image was inserted successfully!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}