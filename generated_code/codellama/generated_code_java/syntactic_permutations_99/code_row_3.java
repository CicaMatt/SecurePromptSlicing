import java.sql.*;  
import java.util.*;  
import java.security.*;
import javax.crypto.*; 
public class Main {  
    public static void main(String[] args) throws Exception{  
        Scanner sc = new Scanner(System.in);  
        String username = sc.nextLine();  
        String password = sc.nextLine();  
        MessageDigest md = MessageDigest.getInstance("SHA-256");  
        byte[] messageDigest = md.digest(password.getBytes());  
        BigInteger no = new BigInteger(1,messageDigest);  
        String hashedPassword = no.toString(16);  
        Class.forName("com.mysql.cj.jdbc.Driver");  
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/userdb","root","root");  
        Statement stmt=con.createStatement();  
        String query = "insert into users (username, password) values ('"+username+"','"+hashedPassword+"')";  
        int x = stmt.executeUpdate(query);  
    }  
}