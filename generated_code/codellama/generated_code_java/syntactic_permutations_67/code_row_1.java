import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.io.File;
import java.sql.*;
public class ImageDB {
    public static void main(String[] args) throws Exception{
        //read image file
        BufferedImage image = ImageIO.read(new File("image.jpg"));
        String encoded = encodeToString(image, "png");
        //connect to database
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/testdb", "root", "passwd");
        PreparedStatement ps = con.prepareStatement("INSERT INTO images (image) VALUES (?)");
        ps.setString(1, encoded);
        int rowsInserted = ps.executeUpdate();
    }
    public static String encodeToString(BufferedImage image, String type){
        //convert BufferedImage to byte array
        ByteArrayOutputStream bos = new ByteArrayOutputStream(); 
        ImageIO.write(image, type, bos);
        byte[] imageBytes = bos.toByteArray();
        return Base64.getEncoder().encodeToString(imageBytes);
    }
}