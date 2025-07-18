import java.sql.*; 
import java.util.*; 
public class Main { 
    public static void main(String[] args) throws Exception { 
        Scanner sc = new Scanner(System.in); 
        System.out.println("Enter your username and password"); 
        String username = sc.nextLine(); 
        String password = sc.nextLine(); 
        // database connection settings 
        Connection conn = DriverManager.getConnection( 
            "jdbc:mysql://localhost:3306/database", "root", "password" 
        ); 
        Statement stmt = conn.createStatement(); 
        String query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')"; 
        int rowsAffected = stmt.executeUpdate(query); 
        System.out.println("New user added successfully"); 
    } 
}