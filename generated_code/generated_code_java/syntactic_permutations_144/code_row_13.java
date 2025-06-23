import java.sql.*;
    
    public class Unsubscribe {
        private static final String DB_URL = "jdbc:mysql://localhost/dbname";
        private static final String USER = "user";
        private static final String PASS = "password";
    
        public static void main(String[] args) throws SQLException {
            Connection conn = null;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(DB_URL, USER, PASS);
    
                String email = "someone@example.com";
    
                PreparedStatement statement = conn.prepareStatement("SELECT id FROM users WHERE email = ?");
                statement.setString(1, email);
    
                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    int unsubscribeResult = unsubscribeFromEmails(email);
                    if (unsubscribeResult == 1) {
                        System.out.println("Unsubscribed successfully");
                    } else {
                        System.out.println("Failed to unsubscribe");
                    }
                } else {
                    System.out.println("Email not found in database");
                }
            } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
            } finally {
                if (conn != null) {
                    conn.close();
                }
            }
        }
    
        private static int unsubscribeFromEmails(String email) throws SQLException {
            Connection conn = null;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(DB_URL, USER, PASS);
    
                PreparedStatement statement = conn.prepareStatement("UPDATE users SET subscribed=0 WHERE email = ?");
                statement.setString(1, email);
    
                int result = statement.executeUpdate();
                return result;
            } catch (ClassNotFoundException ex) {
                ex.printStackTrace();
            } finally {
                if (conn != null) {
                    conn.close();
                }
            }
        }
    }