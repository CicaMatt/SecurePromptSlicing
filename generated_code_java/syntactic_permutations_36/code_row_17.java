import java.sql.*;
    public class Login {
    	public static boolean login(String username, String password) {
    		// get database connection
            Connection conn = null;
            Statement stmt = null;
            ResultSet rs = null;
            String dbUrl = "jdbc:mysql://localhost/mydb";
            try {
                conn = DriverManager.getConnection(dbUrl, "root", "password");
                stmt = conn.createStatement();
                // query database for username and password match
                rs = stmt.executeQuery("SELECT * FROM users where username='" + username + "' AND password='" + password + "'");
                if (rs.next()) {
                    return true;
                } else {
                    return false;
                }
            } catch (SQLException ex) {
            	return false;
            } finally {
            	// close database connection
                rs.close();
                stmt.close();
                conn.close();
            }
    	}
    }