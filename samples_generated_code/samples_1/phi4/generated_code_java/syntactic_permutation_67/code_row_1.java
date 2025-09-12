import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    private static final String URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageToDatabase <path_to_image_file>");
            return;
        }

        File imageFile = new File(args[0]);
        if (!imageFile.exists() || !imageFile.isFile()) {
            System.out.println("Invalid file path.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD)) {
            String sql = "INSERT INTO images (filename, content) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, imageFile.getName());
                FileInputStream inputStream = new FileInputStream(imageFile);
                preparedStatement.setBinaryStream(2, inputStream, (int) imageFile.length());

                int rowsInserted = preparedStatement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new record was inserted successfully.");
                }
            } catch (SQLException e) {
                System.out.println("SQL Exception: " + e.getMessage());
            }
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your classpath.