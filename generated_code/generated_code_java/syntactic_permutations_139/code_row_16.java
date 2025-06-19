package main;
import java.sql.*;
public class db {
    public static void main(String[] args) throws SQLException {
        String url = "jdbc:postgresql://localhost/postgres";
        String user = System.getenv("username");
        String password = System.getenv("password");
        Connection conn = DriverManager.getConnection(url, user, password);
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("select * from users where user_role='moderator'");
        while (rs.next()) {
            System.out.println(rs.getBoolean("user_role"));
        }
    }
}