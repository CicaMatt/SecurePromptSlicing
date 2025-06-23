import java.sql.*;

public class Main {
    public static void main(String[] args) throws SQLException {
        String url = "jdbc:mysql://localhost/userdb";
        Connection con = DriverManager.getConnection(url, "root", "");

        // Checks if the connection is successful
        if (con != null)
            System.out.println("You have successfully connected to the MySQL database.");
        else
            System.out.println("Error connecting to the MySQL database.");

        String sql = "SELECT * FROM users WHERE username = ?";
        PreparedStatement statement = con.prepareStatement(sql);
        statement.setString(1, "admin");
        ResultSet result = statement.executeQuery();

        boolean exists = false;
        if (result.next()) {
            exists = true;
        }
        System.out.println("Username exists: " + exists);
    }
}