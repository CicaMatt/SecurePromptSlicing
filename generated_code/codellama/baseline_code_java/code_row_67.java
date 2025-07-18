import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Properties;
import javax.imageio.ImageIO;

public class ImageUploader {
   public static void main(String[] args) throws Exception {
      // Load JDBC driver and connect to database
      Properties properties = new Properties();
      properties.setProperty("user", "root");
      properties.setProperty("password", "");
      Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/image_db", properties);
      
      // Load image file and convert it to a byte array
      FileInputStream inputStream = new FileInputStream("my-image.png");
      ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
      ImageIO.write(ImageIO.read(inputStream), "PNG", outputStream);
      outputStream.close();
      byte[] imageData = outputStream.toByteArray();
      
      // Save the image data into a MySQL table
      PreparedStatement statement = conn.prepareStatement("INSERT INTO images (image_data) VALUES (?)");
      statement.setBytes(1, imageData);
      statement.executeUpdate();
   }
}