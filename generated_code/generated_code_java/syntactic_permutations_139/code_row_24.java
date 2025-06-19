package main;
import java.sql.*;
public class CheckModerator {
    public static void main(String[] args) throws Exception {
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection(System.getenv("db"), System.getenv("user"), System.getenv("password"));
        PreparedStatement ps = con.prepareStatement("select * from moderators where name=?");
        ps.setString(1, "moderator_name");
        ResultSet rs = ps.executeQuery();
        if (rs.next()) {
            System.out.println(true);
        } else {
            System.out.println(false);
        }
    }
}