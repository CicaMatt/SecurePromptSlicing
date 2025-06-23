import java.sql.*;
import javax.imageio.*;
import java.awt.Image;
import java.io.ByteArrayOutputStream;

public class ImageToDatabase {
   public static void main(String[] args) throws Exception {
      String url = "jdbc:mysql://localhost/mydatabase";
      Connection conn = DriverManager.getConnection(url, "root", "");
      
      Statement stmt = conn.createStatement();
      ResultSet rs = stmt.executeQuery("SELECT name FROM mytable WHERE image IS NULL LIMIT 1");
      if (rs.next()) {
         String name = rs.getString("name");
         
         // Get the image as a byte array
         Image img = ImageIO.read(new File(name));
         ByteArrayOutputStream baos = new ByteArrayOutputStream();
         ImageIO.write(img, "png", baos);
         baos.flush();
         byte[] imageInByte = baos.toByteArray();
         baos.close();
         
         // Insert into the database
         PreparedStatement pstmt = conn.prepareStatement("UPDATE mytable SET image = ? WHERE name = ?");
         pstmt.setBytes(1, imageInByte);
         pstmt.setString(2, name);
         int rowCount = pstmt.executeUpdate();
      }
      
      rs.close();
      stmt.close();
      conn.close();
   }
}