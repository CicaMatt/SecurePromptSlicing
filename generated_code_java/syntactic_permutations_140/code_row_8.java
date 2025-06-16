import java.sql.*;

public class DatabaseConnection {
  public static void main(String[] args) throws Exception {
	    String url = "jdbc:mysql://localhost:3306/";
	    Connection conn = null;
	    PreparedStatement ps = null;
	    ResultSet rs = null;

	    try {
	        Class.forName("com.mysql.cj.jdbc.Driver");
	        conn = DriverManager.getConnection(url, "root", "root"); // username and password for the MySQL database

	        String query = "SELECT * FROM users WHERE username=?"; // create the SQL query
	        ps = conn.prepareStatement(query); // prepare statement
	        ps.setString(1, "username"); // set input parameter 1 to the username in the query
	        rs = ps.executeQuery(); // execute query and store the result set

	        if (rs.next()) {
	            System.out.println("Username exists");
	        } else {
	            System.out.println("Username does not exist");
	        }
	    } catch (SQLException e) {
	        e.printStackTrace();
	    } finally {
	        if (rs != null)
	            rs.close();
	        if (ps != null)
	            ps.close();
	        if (conn != null)
	            conn.close(); // close connection
	    }
  }
}