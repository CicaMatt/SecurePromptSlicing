import java.io.File;
import java.io.FileInputStream;
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

        String filePath = args[0];
        File file = new File(filePath);

        if (!file.exists()) {
            System.out.println("File not found: " + filePath);
            return;
        }

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", "your_username", "your_password")) {

            String sql = "INSERT INTO images_table (image) VALUES (?)";

            try (PreparedStatement pstmt = connection.prepareStatement(sql)) {
                FileInputStream fis = new FileInputStream(file);
                pstmt.setBinaryStream(1, fis, (int) file.length());
                pstmt.executeUpdate();
                System.out.println("Image stored successfully.");
            }

        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}


**Note:** Replace `your_database_name`, `your_username`, and `your_password` with your actual database details. Ensure that the MySQL JDBC driver is included in your project's classpath.