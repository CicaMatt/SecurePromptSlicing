import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class Database {
    private String jdbcURL = "jdbc:mysql://localhost:3306/java_db"; // the database name is java_db
    private String username = "root";
    private String password = "";
    
    public static void main(String[] args) throws Exception {
        Database db = new Database();
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address: ");
        String emailAddress = scanner.nextLine();
        
        db.unsubscribe(emailAddress);
    }
    
    public void unsubscribe(String emailAddress) throws Exception {
        // connect to the database
        Connection con = DriverManager.getConnection(jdbcURL, username, password);
        
        String sql = "SELECT * FROM subscribers WHERE email_address=?";
        PreparedStatement stmt = con.prepareStatement(sql);
        stmt.setString(1, emailAddress);
        ResultSet rs = stmt.executeQuery();
        
        if (rs.next()) {
            // email address is in the database
            sql = "DELETE FROM subscribers WHERE email_address=?";
            PreparedStatement deleteStmt = con.prepareStatement(sql);
            deleteStmt.setString(1, emailAddress);
            
            System.out.println("You have been unsubscribed.");
        } else {
            // email address is not in the database
            System.out.println("You are already unsubscribed.");
        }
        
        rs.close();
        stmt.close();
        con.close();
    }
}