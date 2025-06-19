import java.sql.*;
import java.util.Scanner;

public class Login {
    public static void main(String[] args) throws SQLException{
        String user,password;
        System.out.println("Username: ");
        Scanner sc = new Scanner(System.in);
        user =sc.nextLine();
        System.out.println("Password: ");
        password=sc.nextLine();
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/login","root","root");
        Statement stmt = (Statement)conn.createStatement();
        ResultSet rs = stmt.executeQuery("select * from login where username='"+user+"' and password='"+password+"'");
        if(rs.next()){
            System.out.println("Login Successful!");
            System.out.println("Welcome "+user);
            System.out.println("You are now redirected to dashboard page");
        }
        else{
            System.out.println("Invalid Login! Redirecting you back to login page...");
            main(args);
        }
    }
}