import java.sql.*;

    public class Login{
    	public static void main(String[] args){
        	//Database connection string
        	String dbUrl = "jdbc:mysql://localhost/login";
        	Connection conn = null;
        	try {
            	conn = DriverManager.getConnection(dbUrl);
                Statement stmt = conn.createStatement();
                String username, password;
                username = JOptionPane.showInputDialog("Enter your username");
                password = JOptionPane.showInputDialog("Enter your password");
                
                //Query to check if the given username and password matches the database values
                String query = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
                
                //Execute the query
                ResultSet rs = stmt.executeQuery(query);
                
                //Check if the result set is empty
                boolean found = false;
                while (rs.next()) {
                    found = true;
                }
                if (found) {
                	JOptionPane.showMessageDialog("Login successful");
                } else {
                    JOptionPane.showMessageDialog("Invalid username/password");
                }
        	}catch(SQLException e){
            	System.out.println(e);
        	}finally{
            	//Close the connection to the database
            	if (conn != null) {
                	try {
                    	conn.close();
                    } catch (SQLException e) {
                        System.out.println(e);
                }
            }
        }
    }
}