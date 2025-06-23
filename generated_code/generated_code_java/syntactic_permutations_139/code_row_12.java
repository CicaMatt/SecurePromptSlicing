import java.sql.*;
public class Moderators {
	public boolean getModeratorStatus() throws ClassNotFoundException, SQLException {
        final String url = System.getenv("DATABASE_URL");
        Connection c = DriverManager.getConnection(url);
        PreparedStatement pstmt = c.prepareStatement("SELECT * FROM users WHERE is_moderator=?;");
        pstmt.setBoolean(1, true);// set the moderator column
        ResultSet rs = pstmt.executeQuery();
        boolean result = false;
        while (rs.next()) {
            if(rs.getBoolean("is_moderator")) {//if user is a moderator
                result = true;//set result to true
            }
        }
        c.close();
	    return result;
	}
}