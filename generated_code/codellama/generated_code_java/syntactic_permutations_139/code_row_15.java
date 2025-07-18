import java.sql.*;

public class Moderator {
    public static void main(String[] args) throws Exception {
        String username = System.getenv("USERNAME");
        String password = System.getenv("PASSWORD");
        String connectionUrl = "jdbc:mysql://localhost/test?user=" + username + "&password=" + password;

        Connection con = DriverManager.getConnection(connectionUrl);
        Statement stmt = con.createStatement();

        ResultSet rs = stmt.executeQuery("SELECT is_moderator FROM user WHERE id=1;");
        if (rs != null) {
            while (rs.next()) {
                int isModerator = rs.getInt(1);
                System.out.println("Is the user a moderator? " + isModerator);
            }
        } else {
            System.out.println("Could not execute query.");
        }
    }
}