import java.io.*;
import java.util.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Base64;

public class SaveImage {
    private String DB_URL = "jdbc:mysql://localhost/image";
    private String USER = "root";
    private String PASSWORD = "password";
    
    public static void main(String[] args) throws Exception{
        Connection con = null;
        Statement stmt = null;
        
        try {
            con = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            stmt = con.createStatement();
            
            String query = "INSERT INTO images VALUES (" + Base64.encodeBase64(new FileInputStream("image.jpg")) + ")";
            stmt.executeUpdate(query);
        } catch (Exception e) {
            System.err.println("Error: " + e);
            throw e;
        } finally {
            if (stmt != null) {
                con.close();
            }
        }
    }
}