import java.security.*;
import java.sql.*;

public class PasswordHash {
    public static void main(String[] args) throws SQLException {
        String username = "username";
        String password = "password";
        String hashedPassword = getHashedPassword(password);
        insertIntoDatabase(username, hashedPassword);
    }
    
    // Generates a hashed password using PBKDF2WithHmacSHA1
    private static String getHashedPassword(String password) {
        int iterations = 1000;
        int saltLength = 32;
        int desiredKeyLen = 256;
        byte[] saltBytes = new byte[saltLength];
        
        SecureRandom secureRandom = new SecureRandom();
        secureRandom.nextBytes(saltBytes);
        
        KeySpec spec = new PBEKeySpec(password.toCharArray(), saltBytes, iterations, desiredKeyLen);
        SecretKeyFactory f;
        try {
            f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
            byte[] keyBytes = f.generateSecret(spec).getEncoded();
            return iterations + ":" + toHex(saltBytes) + ":" + toHex(keyBytes);
        } catch (NoSuchAlgorithmException | InvalidKeySpecException e) {
            throw new RuntimeException(e);
        }
    }
    
    // Inserts the username and hashed password into a database. This function is not tested here, 
    // but it should be tested in your unit test code.
    private static void insertIntoDatabase(String username, String hashedPassword) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
            String sql = "INSERT INTO users (username, password) VALUES (?, ?);";
            
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);
            pstmt.executeUpdate();
        } catch (ClassNotFoundException e) {
            throw new RuntimeException("JDBC driver not found", e);
        } finally {
            if (pstmt != null) {
                try {
                    pstmt.close();
                } catch (SQLException e) {
                    // do nothing
                }
            }
            
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    // do nothing
                }
            }
        }
        
    }
    
    // Converts byte[] to hexadecimal string representation
    private static String toHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < bytes.length; ++i) {
            sb.append(Integer.toString((bytes[i] & 0xff) + 0x100, 16).substring(1));
        }
        
        return sb.toString();
    }
}