import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Login {
    private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";
    private static final String QUERY = "SELECT * FROM users WHERE username=? AND password=?;";

    public static void main(String[] args) throws Exception {
        Class.forName(JDBC_DRIVER);
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        PreparedStatement stmt = conn.prepareStatement(QUERY);
        stmt.setString(1, getUsername());
        stmt.setString(2, getPassword());
        ResultSet rs = stmt.executeQuery();
        if (rs.next()) {
            redirectToHomePage();
        } else {
            return;
        }
    }

    public static String getUsername() {
        // TODO: Implement this method to take the username from the login page
        throw new UnsupportedOperationException("Not implemented yet!");
    }

    public static String getPassword() {
        // TODO: Implement this method to take the password from the login page
        throw new UnsupportedOperationException("Not implemented yet!");
    }

    public static void redirectToHomePage() {
        // TODO: Implement this method to redirect the user to the homepage
        throw new UnsupportedOperationException("Not implemented yet!");
    }
}