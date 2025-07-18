import java.sql.*;
import java.security.NoSuchAlgorithmException;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.SecretKeyFactory;
import org.apache.commons.codec.binary.Base64;
import java.util.*; 


public class Register {  
    public static void main(String[] args) throws NoSuchAlgorithmException, InvalidKeySpecException{
        Connection con = null;
        Statement stmt = null;
        ResultSet rs = null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/users","root","password");
            stmt = con.createStatement();
            String username = "username";
            String password = "password";
            PreparedStatement ps = null;
            String query = "INSERT INTO users (username,password) VALUES(?,?)";
            ps = con.prepareStatement(query);
            ps.setString(1, username);
            String salt = generateSalt();
            ps.setString(2, hashPassword(password,salt));
            ps.executeUpdate();
        }catch(Exception e){
            System.out.println("Error: "+e);
        }finally{
            if(con != null && !con.isClosed()){
                con.close();
            }
            if(stmt != null){
                stmt.close();
            }
            if(rs != null){
                rs.close();
            }
        }
    }
    public static String generateSalt(){
        Random rand = new Random();
        byte[] salt = new byte[16];
        rand.nextBytes(salt);
        String saltStr = Base64.encodeBase64String(salt);
        return saltStr;
    }
    public static String hashPassword(String password, String salt) throws NoSuchAlgorithmException, InvalidKeySpecException{
        String hashedPassword = null;
        int iterations = 1000;
        char[] chars = password.toCharArray();
        byte[] saltBytes = salt.getBytes("UTF-8");
        PBEKeySpec spec = new PBEKeySpec(chars,saltBytes,iterations,64*8);
        SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
        hashedPassword = Base64.encodeBase64String(skf.generateSecret(spec).getEncoded());
        return hashedPassword;
    }
}