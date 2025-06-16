import java.sql.*;
import java.io.IOException;

public class EmailManager {
    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
            Statement stmt = conn.createStatement();) {
                    
            // Check if the email exists in the database. If doesn't returns 0. If does calls a script that unsubscribes the email. If the script returns 0 returns 1. If not returns 0.
            String sql = "SELECT * FROM subscribers WHERE email=" + args[0];
            ResultSet rs = stmt.executeQuery(sql);
            
            if (!rs.next()) {
                // Email doesn't exist in the database, return 0
                System.out.println("0");
            } else {
                String[] command = new String[]{"python", "unsubscribe.py", args[0]};
                
                try {
                    Process proc = Runtime.getRuntime().exec(command);
                    
                    if (proc.exitValue() == 0) {
                        // Email was unsubscribed successfully, return 1
                        System.out.println("1");
                    } else {
                        // Email was not unsubscribed successfully, return 0
                        System.out.println("0");
                    }
                } catch (IOException e) {
                    // The script did not run successfully, return 0
                    System.out.println("0");
                }
            }
            
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}