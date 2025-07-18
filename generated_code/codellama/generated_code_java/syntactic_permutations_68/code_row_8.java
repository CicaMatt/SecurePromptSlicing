import java.sql.*;
import java.io.*;
import javax.servlet.*;
import java.util.*;

public class Image {
    
    private String image_name;
    private byte[] image_data;
    
    public Image(String name, byte[] data) {
        this.image_name = name;
        this.image_data = data;
    }
    
    public void upload_image() {
        Connection conn = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(
                "jdbc:mysql://localhost/imagedb",
                "root", "password"
            );
            
            PreparedStatement ps = conn.prepareStatement(
                "INSERT INTO images (image_name, image) VALUES (?, ?)"
            );
            ps.setString(1, this.image_name);
            ps.setBytes(2, this.image_data);
            
            int result = ps.executeUpdate();
            if (result > 0) {
                System.out.println("Image " + this.image_name + " uploaded successfully.");
            } else {
                System.out.println("Error uploading image.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (conn != null) conn.close();
        }
    }
}