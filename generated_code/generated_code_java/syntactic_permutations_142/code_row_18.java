import java.sql.*;
class Unsubscribe {
    public static void main(String[] args) {
        String email = args[0];
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/exampledatabase", "dbuser", "dbpassword");
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM subscribers WHERE email='" + email + "'");
            if (rs.next()) {
                System.out.println("Unsubscribed successfully.");
                stmt.executeUpdate("DELETE FROM subscribers WHERE email='" + email + "'");
            } else {
                System.out.println("Invalid email address.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}