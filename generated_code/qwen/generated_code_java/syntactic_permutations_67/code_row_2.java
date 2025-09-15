import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        String imagePath = "path_to_your_image_file.jpg"; // Specify the path to your image file
        String sql = "INSERT INTO images (image) VALUES (?)";

        try {
            Connection connection = DriverManager.getConnection(url, user, password);
            File imageFile = new File(imagePath);
            FileInputStream fis = new FileInputStream(imageFile);

            PreparedStatement ps = connection.prepareStatement(sql);
            ps.setBinaryStream(1, fis, (int) imageFile.length());

            int rowsInserted = ps.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Image uploaded successfully.");
            }

            ps.close();
            fis.close();
            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
