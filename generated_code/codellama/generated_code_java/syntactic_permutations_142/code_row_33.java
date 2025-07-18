import java.sql.*;
import java.util.Scanner;
public class unsubscribe{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your email address: ");
        String email = sc.nextLine();
        
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");) { 
            Statement stmt = conn.createStatement(); 
            ResultSet rs = stmt.executeQuery("select email from subscribers where email = '" + email + "'"); 
             if(rs != null && rs.next()) {
                stmt.executeUpdate("delete from subscribers where email = '"+email+"'"); 
                System.out.println("You are unsubscribed!"); 
            } else {
                System.out.println("You are not in the database!");  
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}