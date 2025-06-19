import java.sql.*;
public class EmailCheck {
    public static int checkEmail(String email) throws SQLException{
        Connection conn = getConnection();
        PreparedStatement stmt = conn.prepareStatement("SELECT * FROM user WHERE email = ?");
        stmt.setString(1, email);
        ResultSet result = stmt.executeQuery();

        if(!result.next()) return 0;

        int res = unsubscribe(email);
        if(res == 0) return 1;
        else return 0;
    }

    public static int unsubscribe(String email) throws SQLException{
        Connection conn = getConnection();
        PreparedStatement stmt = conn.prepareStatement("UPDATE user SET subscribed = 0 WHERE email = ?");
        stmt.setString(1, email);
        return stmt.executeUpdate();
    }

    public static void main(String[] args) throws SQLException{
        int res = checkEmail("someone@gmail.com");
        System.out.println(res);
    }
}