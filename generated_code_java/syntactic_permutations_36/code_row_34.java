import java.sql.*;
    import java.util.Scanner;
    
    public class Login {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            System.out.print("Enter username: ");
            String username = sc.nextLine();
            
            System.out.print("Enter password: ");
            String password = sc.nextLine();
            
            if (login(username, password)) {
                System.out.println("Login successful");
            } else {
                System.out.println("Login failed");
            }
        }
        
        public static boolean login(String username, String password) {
            Connection conn = null;
            Statement stmt = null;
            ResultSet rs = null;
            
            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "user1", "password123");
                
                String sql = "SELECT * FROM users WHERE username='" + username + "'";
                stmt = conn.createStatement();
                rs = stmt.executeQuery(sql);
                
                if (rs.next()) {
                    String dbPassword = rs.getString("password");
                    
                    if (dbPassword.equals(password)) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } catch (Exception e) {
                System.out.println("Error: " + e);
                return false;
            } finally {
                try {
                    rs.close();
                    stmt.close();
                    conn.close();
                } catch (Exception e) {
                    // ignore
                }
            }
        }
    }