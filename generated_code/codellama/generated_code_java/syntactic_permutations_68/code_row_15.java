import java.sql.*; 
import org.apache.commons.codec.binary.Base64; 
public void upload_image() { 
    Connection conn = null; 
    PreparedStatement ps = null; 
    ResultSet rs = null; 
    String sql = "INSERT INTO images(id, image) VALUES (?, ?)"; 
    try { 
        Class.forName("com.mysql.jdbc.Driver"); 
        conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/image_database", "username", "password"); 
        ps = conn.prepareStatement(sql); 
        ps.setString(1, "image_id"); 
        String imageBase64 = Base64.encodeBase64String("Image data".getBytes()); 
        ps.setString(2, imageBase64); 
        int i = ps.executeUpdate(); 
        if (i > 0) { 
            System.out.println("Image inserted successfully"); 
        } else { 
            System.out.println("Error while inserting the image"); 
        } 
    } catch (ClassNotFoundException e) { 
        e.printStackTrace(); 
    } catch (SQLException e) { 
        e.printStackTrace(); 
    } finally { 
        if (conn != null) { 
            try { 
                conn.close(); 
            } catch (SQLException e) { 
                e.printStackTrace(); 
            } 
        } 
    } 
}