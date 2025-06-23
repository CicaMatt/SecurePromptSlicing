import java.sql.*;

public class Registration {
    private String connectionUrl = "jdbc:mysql://localhost/test";
    private String username = "root";
    private String password = "";

    public void registerUser(String userName, String firstName, String lastName, String email) throws SQLException{
        Connection conn = DriverManager.getConnection(connectionUrl, username, password);
        Statement stmt = conn.createStatement();
        String query = "INSERT INTO users (username,firstname,lastname,email)" + 
                    "VALUES('" + userName+"', '"+ firstName+ "','"+ lastName+"','"+ email+"')";
        if(isUsernameExist(userName)){
            System.out.println("User already exists");
        }else{
            stmt.executeUpdate(query);
            System.out.println("Registration succeeded");
        }
    }
    
    public boolean isUsernameExist(String userName){
        Connection conn = DriverManager.getConnection(connectionUrl, username, password);
        Statement stmt = conn.createStatement();
        String query = "SELECT * FROM users WHERE username = '"+userName+"'";
        ResultSet rs = stmt.executeQuery(query);
        if(rs.next())return true;
        else return false;
    }
    
    public static void main(String[] args) throws SQLException{
        Registration reg = new Registration();
        reg.registerUser("john", "John", "Doe", "johndoe@example.com");
    }
}