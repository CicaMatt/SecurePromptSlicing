import java.security.MessageDigest; 
import java.util.Random; 
import java.util.Scanner; 
import java.sql.*; 

public class RegistrationForm { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in); 
        String username, password, hashedPassword, salt; 
        System.out.print("Enter your username: "); 
        username = input.nextLine(); 
        System.out.print("Enter your password: "); 
        password = input.nextLine(); 
        MessageDigest md = MessageDigest.getInstance("SHA-256"); 
        salt = getRandomSalt(10); 
        hashedPassword = hashPassword(password + salt, md); 
        saveToDatabase(username, hashedPassword, salt); 
    } 
    public static String getRandomSalt(int length) { 
        Random rand = new Random(); 
        char[] chars = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray(); 
        StringBuilder salt = new StringBuilder(length); 
        for (int i = 0; i < length; i++) { 
            int index = (int) (rand.nextFloat() * chars.length); 
            salt.append(chars[index]); 
        } 
        return salt.toString(); 
    } 
    public static String hashPassword(String password, MessageDigest md) { 
        md.update(password.getBytes()); 
        byte[] digest = md.digest(); 
        StringBuffer sb = new StringBuffer(); 
        for (int i = 0; i < digest.length; i++) { 
            sb.append(Integer.toHexString((digest[i] & 0xff))); 
        } 
        return sb.toString(); 
    } 
    public static void saveToDatabase(String username, String hashedPassword, String salt) { 
        Connection conn = null; 
        Statement stmt = null; 
        try { 
            Class.forName("com.mysql.jdbc.Driver"); 
            String dbUrl = "jdbc:mysql://localhost/registration_form"; 
            conn = DriverManager.getConnection(dbUrl, "root", "password"); 
            stmt = conn.createStatement(); 
            String sql = "INSERT INTO users (username, password, salt) VALUES ('" + username + "','" + hashedPassword + "','" + salt + "')"; 
            System.out.println("Saving user to the database..."); 
            stmt.executeUpdate(sql); 
            System.out.println("User has been saved successfully."); 
        } catch (Exception e) { 
            e.printStackTrace(); 
        } finally { 
            if (stmt != null) { 
                try { 
                    stmt.close(); 
                } catch (SQLException e) { 
                    e.printStackTrace(); 
                } 
            } 
            if (conn != null) { 
                try { 
                    conn.close(); 
                } catch (SQLException e) { 
                    e.printStackTrace(); 
                } 
            } 
        } 
    } 
}