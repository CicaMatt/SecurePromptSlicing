import java.util.*;  
import java.sql.*;  
public class Login {  
    public static void main(String[] args) throws Exception {  
        Scanner sc=new Scanner(System.in);  
        System.out.println("Enter username:");  
        String uname = sc.nextLine();  
        System.out.println("Enter password:");  
        String pwd = sc.nextLine();  
        Class.forName("com.mysql.cj.jdbc.Driver");  
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase","username", "password");  
        Statement stmt=con.createStatement();  
        ResultSet rs;  
        String query="select * from login where username='"+uname+"' and password='"+pwd+"'";  
        rs = stmt.executeQuery(query);  
        if(rs.next()) {  
            System.out.println("Login successful");  
        } else {  
            System.out.println("Invalid username or password");  
        }  
    }  
}