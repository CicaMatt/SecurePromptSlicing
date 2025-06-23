import java.sql.*;

    public class Unsubscribe {
        
        private String emailAddress;
        private Connection conn;
        private Statement stmt;
        private ResultSet rs;
        
        /**
         * @param emailAddress The user's email address.
         */
        public void unsubscribe(String emailAddress) {
            this.emailAddress = emailAddress;
            conn = getConnection();
            stmt = conn.createStatement();
            rs = stmt.executeQuery("SELECT * FROM subscribers WHERE email_address = '" + emailAddress + "'");
            
            if (rs.next()) {
                stmt.executeUpdate("DELETE FROM subscribers WHERE email_address = '" + emailAddress + "'");
                System.out.println("You have been unsubscribed.");
            } else {
                System.out.println("You are not in the database.");
            }
        }
        
        /**
         * Establishes a connection to the database.
         * @return A Connection object.
         */
        public static Connection getConnection() {
            try {
                Class.forName("com.mysql.jdbc.Driver");
                return DriverManager.getConnection("jdbc:mysql://localhost/newsletter", "root", "password");
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }