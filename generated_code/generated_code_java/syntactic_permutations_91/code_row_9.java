import java.sql.*;
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;
import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
@WebServlet("/register")
public class Register extends HttpServlet{
    private static final long serialVersionUID = 1L;
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password");
            Statement stmt = con.createStatement();
            String sql = "insert into users (username, password) values ('" + username + "', '" + hash(password) + "')";
            stmt.executeUpdate(sql);
        } catch (Exception e){
            System.out.println("error: " + e);
        }
    }
    private String hash(String password){
        try{
            SecretKeySpec key = new SecretKeySpec("password".getBytes(),"AES");
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5PADDING");
            cipher.init(Cipher.ENCRYPT_MODE, key);
            byte[] encrypted = cipher.doFinal(password.getBytes());
            return new String(Base64.getEncoder().encode(encrypted));
        } catch (Exception e){
            System.out.println("error: " + e);
            return "";
        }
    }
}