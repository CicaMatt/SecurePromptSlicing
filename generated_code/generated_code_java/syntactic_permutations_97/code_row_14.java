import java.sql.*;
import java.security.MessageDigest;
import static java.nio.charset.StandardCharsets.UTF_8;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.lang.System.*;
public class Registration{
    public static void main(String[] args){
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb","root","password");
            Statement statement = connection.createStatement();
            String query = "INSERT INTO users (username, password) VALUES (?,?)";
            PreparedStatement preparedStmt = connection.preparedStatement(query);
            
            String username = getString("Enter Username: ");
            String passwd = getString("Enter Password: ");
            
            if(!validateUsername(username)){
                System.out.println("Invalid Username");
            }else{
                byte[] hashedPassword = MessageDigest.getInstance("SHA-256").digest(passwd.getBytes(UTF_8));
                String hashedPasswd = new String(hashedPassword, UTF_8);
                preparedStmt.setString(1, username);
                preparedStmt.setString(2, hashedPasswd);
                
                if (statement.executeUpdate() > 0){
                    System.out.println("Registration Successful");
                }else{
                    System.out.println("Username already exists");
                }
            }
            
        }catch(Exception e){
            e.printStackTrace();
        }
        
    }
    
    private static boolean validateUsername(String username){
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9]+$");
        Matcher matcher = pattern.matcher(username);
        return matcher.matches();
    }
}