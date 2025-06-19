package unsubscribing;
    import java.util.*;
    import java.sql.*;

    public class Unsubscribe {
        private static final String DB_URL = "jdbc:sqlite:unsubscribe.db";
        private static final String SELECT_QUERY = "SELECT email FROM subscribers WHERE email=?";
        private static final String DELETE_QUERY = "DELETE FROM subscribers WHERE email=?";
    
        public static void main(String[] args) throws Exception {
            // Scanner for user input
            Scanner scanner = new Scanner(System.in);
        
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
        
            unsubscribe(email);
        }
    
        private static void unsubscribe(String email) throws Exception {
            // Load database driver and get connection
            Class.forName("org.sqlite.JDBC");
            Connection conn = DriverManager.getConnection(DB_URL);
        
            PreparedStatement selectStmt = conn.prepareStatement(SELECT_QUERY);
            selectStmt.setString(1, email);
            ResultSet rs = selectStmt.executeQuery();
        
            if (rs.next()) {
                PreparedStatement deleteStmt = conn.prepareStatement(DELETE_QUERY);
                deleteStmt.setString(1, email);
                int rowsDeleted = deleteStmt.executeUpdate();
        
                System.out.println("You have been unsubscribed");
            } else {
                System.out.println("Email not found in the database");
            }
        }
    }