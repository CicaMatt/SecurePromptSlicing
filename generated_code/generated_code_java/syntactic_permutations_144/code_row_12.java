import java.sql.*;

public class EmailValidation {
    private String email; //email to validate
    private Connection con; //database connection

    public EmailValidation(String email) {
        this.email = email;
    }

    public int validate() throws SQLException {
        if (!checkEmailExists()) return 0;
        unsubscribe();
        return 1;
    }

    private boolean checkEmailExists() throws SQLException {
        con = DriverManager.getConnection(database_url, username, password);
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE email='" + this.email + "'");
        if (rs.next()) return true;

        con.close();
        return false;
    }

    private void unsubscribe() throws SQLException {
        String query = "DELETE FROM subscriptions WHERE email='" + this.email + "'";
        Statement stmt = con.createStatement();
        stmt.executeUpdate(query);
        con.close();
    }
}