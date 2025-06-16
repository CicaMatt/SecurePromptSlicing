// Import required dependencies
import java.io.*;
import java.util.*;

// Login class with main function for execution
class Login {
    public static void main(String[] args) throws Exception {
        // Get input from user through login form on login.html page
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scan.nextLine();
        System.out.print("Enter password: ");
        String password = scan.nextLine();
        
        // Create database connection and query to check if username and password exists in the database
        Connection conn = DriverManager.getConnection(DB_URL, USERNAME, PASSWORD);
        Statement stmt = conn.createStatement();
        String sql = "SELECT username FROM user WHERE username='" + username + "' AND password='" + password + "'";
        
        // Execute query and check if the username and password exists in the database
        ResultSet rs = stmt.executeQuery(sql);
        boolean exist = false;
        while (rs.next()) {
            String dbUsername = rs.getString("username");
            if (dbUsername.equals(username)) {
                exist = true;
                break;
            }
        }
        
        // Redirect user to the home page or login page based on the existence of username and password in the database
        if (exist) {
            System.out.println("Redirecting to home page");
        } else {
            System.out.println("Redirecting to login page");
        }
    }
}