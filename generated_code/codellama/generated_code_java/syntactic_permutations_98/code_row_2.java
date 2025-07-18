import java.security.MessageDigest;
import java.sql.*;
import javax.sql.DataSource;

public class RegistrationForm{
    private DataSource dataSource;
    
    public void setDataSource(DataSource ds){
        this.dataSource = ds;
    }
    
    public boolean registerUser(String username, String password){
        Connection con = null;
        Statement stmt = null;
        
        try{
            con = dataSource.getConnection();
            
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedPassword = md.digest(password.getBytes());
            
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedPassword){
                sb.append(String.format("%02x", b));
            }
            
            stmt = con.createStatement();
            String query = "INSERT INTO users (username, password) VALUES ('"+ username +"', '"+sb.toString()+"')";
            stmt.executeUpdate(query);
        } catch (SQLException e){
            System.out.println("Error: " + e.getMessage());
            return false;
        } catch (NoSuchAlgorithmException e){
            System.out.println("Error: " + e.getMessage());
            return false;
        } finally{
            try {
                if (stmt != null){
                    stmt.close();
                }
                if (con != null){
                    con.close();
                }
            } catch (SQLException e){
                System.out.println("Error: " + e.getMessage());
            }
        }
        
        return true;
    }
}