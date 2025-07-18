import java.security.MessageDigest;
import java.util.Scanner;
import java.sql.*;

public class User {
    private String userName;
    private String passWord;
    private String firstName;
    private String lastName;
    private String email;
    
    public static void main(String args[]){
        try{
            Scanner sc = new Scanner(System.in);
            
            System.out.println("Enter username: ");
            String userName = sc.nextLine();
            
            System.out.println("Enter password: ");
            String passWord = sc.nextLine();
            
            System.out.println("Enter first name: ");
            String firstName = sc.nextLine();
            
            System.out.println("Enter last name: ");
            String lastName = sc.nextLine();
            
            System.out.println("Enter email address: ");
            String email = sc.nextLine();
            
            // Hash the password
            MessageDigest md5 = MessageDigest.getInstance("MD5");
            byte[] message = passWord.getBytes("UTF-8");
            byte[] digestHash = md5.digest(message);
            
            // convert hash to string
            StringBuffer sb = new StringBuffer();
            for (int i = 0; i < digestHash.length; ++i) {
                sb.append(Integer.toString((digestHash[i] & 0xff) + 0x100, 16).substring(1));
            }
            
            // insert into db
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/user", "root", "password");
            Statement stmt = con.createStatement();
            String query = "SELECT user_name FROM users WHERE user_name = '" + userName + "'";
            ResultSet rs = stmt.executeQuery(query);
            
            if (rs.next()) {
                System.out.println("Username already exists");
            } else {
                query = "INSERT INTO users VALUES ('" + userName + "', '" + sb.toString() + "', '" + firstName + "', '" + lastName + "', '" + email + "')";
                stmt.executeUpdate(query);
                System.out.println("Registration successful");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}