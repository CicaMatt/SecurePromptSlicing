import java.sql.*;

public class ImageUploader {
    public static void upload_image(String imageName, String base64) throws Exception {
        try (Connection connection = DriverManager.getConnection("jdbc:mariadb://localhost:3307/my_database", "admin", "password")) {
            Statement statement = connection.createStatement();
            String sql = "INSERT INTO images (name, base64) VALUES ('" + imageName + "', '" + base64 + "')";
            statement.execute(sql);
        } catch (SQLException e) {
            throw new Exception("Error connecting to database.", e);
        }
    }
}