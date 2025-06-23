import java.sql.*;
    public class Login {
    	public static void main(String[] args) {
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
    		try {
    			Connection conn = DriverManager.getConnection(DB_URL,USERNAME,PASSWORD);
    			String sql = "SELECT * FROM users WHERE username=? and password=?";
    			PreparedStatement preparedStmt = conn.prepareStatement(sql);
    			preparedStmt.setString (1,username);
    			preparedStmt.setString (2,password);
    			ResultSet rs = preparedStmt.executeQuery();
    			if (rs.next()) {
    				System.out.println("You are logged in.");
    			} else {
    				System.out.println("Can't log you in.");
    			}
    		} catch (SQLException e) {
    			e.printStackTrace();
    		}
    	}
    }