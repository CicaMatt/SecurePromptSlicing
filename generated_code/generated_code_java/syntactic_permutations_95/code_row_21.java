import java.security.NoSuchAlgorithmException;
import java.sql.*;
import java.util.Random;
import java.security.SecureRandom;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.SecretKeySpec;

public class Registration {
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/mydb";
    static final String USER = "root"; // username
    static final String PASS = ""; // password
    
    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try{
            // STEP 2: Register JDBC driver
            Class.forName("com.mysql.jdbc.Driver");
            
            // STEP 3: Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            // STEP 4: Execute a query
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            String sql;
            sql = "SELECT username, password FROM users";
            rs = stmt.executeQuery(sql);
            
            // STEP 5: Extract data from result set
            while(rs.next()){
                String username = rs.getString("username");
                byte[] salt = rs.getBytes("salt");
                System.out.println("Username: " + username);
                //STEP6 : Hash the password and generate a random salt.
                SecureRandom secureRandom = new SecureRandom();
                String generatedPassword = getGeneratedPassword(username,secureRandom);
                
                //STEP7 : Prepare a query to insert user details into database
                sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
                ps = conn.prepareStatement(sql);
                ps.setString(1, username);
                ps.setBytes(2, generatedPassword.getBytes("UTF-8"));
                ps.setBytes(3, salt); 
                
                //STEP 8: Execute the query
                ps.executeUpdate();
                System.out.println("User details inserted into database.");
            }
            rs.close();
        }catch(SQLException se){
            se.printStackTrace();
        }catch(ClassNotFoundException cnfe){
            cnfe.printStackTrace();
        }finally{
            try{
                if(stmt!=null) stmt.close();
            }catch(SQLException se2){
            }//nothing we can do
            
            try{
                if(conn!=null) conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }
        }
    }
    private static String getGeneratedPassword(String username, SecureRandom secureRandom) throws NoSuchAlgorithmException {
		byte[] salt = new byte[16];
		secureRandom.nextBytes(salt);
		KeySpec spec = new PBEKeySpec(username.toCharArray(), salt, 65536, 256);
		SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
		return toHex(f.generateSecret(spec).getEncoded());
	}
    private static String toHex(byte[] array) {
        BigInteger bi = new BigInteger(1, array);
        return String.format("%0" + (array.length << 1) + "X", bi);
    }
}