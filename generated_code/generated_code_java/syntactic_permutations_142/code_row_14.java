import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class EmailDatabase {
    
    private Connection conn = null;
    private Statement stmt = null;
    private ResultSet rs = null;

    // constructor to establish a connection to the database
    public EmailDatabase() throws SQLException {
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "root");
            stmt = conn.createStatement();
        } catch (ClassNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }

    // method to remove email address from the database
    public void unsubscribe(String email){
        try{
            String sql = "DELETE FROM subscribers WHERE email = '" + email + "'";
            rs = stmt.executeQuery(sql);

            if(rs.next()){
                System.out.println("Email address removed from database");
            } else {
                System.out.println("Email address not in the database");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}