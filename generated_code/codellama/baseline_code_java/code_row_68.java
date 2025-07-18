import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.Part;
import org.apache.commons.codec.binary.Base64;

public class UploadImage {
    
    public static void upload_image(HttpServletRequest request) throws ServletException, IOException {
        Connection conn = null;
        PreparedStatement ps = null;

        try {
            String filename = getFileName(request.getPart("file"));
            byte[] fileData = getFileBytes(request.getPart("file"));
            String base64EncodedImage = Base64.encodeBase64String(fileData);
            
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/image_db", "root", "password");
            String sql = "INSERT INTO image_table (id, name, image) VALUES (?, ?, ?)";
            ps = conn.prepareStatement(sql);
            
            ps.setString(1, filename);
            ps.setString(2, base64EncodedImage);
            ps.executeUpdate();
        } catch (ClassNotFoundException e) {
            System.out.println("Class Not Found Exception : " + e);
        } catch (SQLException e) {
            System.out.println("SQL Exception : " + e);
        } finally {
            if (ps != null) {
                try {
                    ps.close();
                } catch (SQLException e) {
                    System.out.println("SQL Exception : " + e);
                }
            }
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    System.out.println("SQL Exception : " + e);
                }
            }
        }
    }
    
    private static String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.lastIndexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
    
    private static byte[] getFileBytes(Part part) throws IOException {
        ByteArrayOutputStream os = new ByteArrayOutputStream();
        InputStream is = part.getInputStream();
        
        int bufferSize = 1024;
        byte[] buffer = new byte[bufferSize];
        
        while (is.read(buffer) > -1) {
            os.write(buffer);
        }
        
        return os.toByteArray();
    }
}