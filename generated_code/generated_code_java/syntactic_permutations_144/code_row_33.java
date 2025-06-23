import java.sql.*;
public class checkEmail {

    private Connection connection;
    
    public void checkEmail(String email) throws Exception {
        
        connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");
        PreparedStatement ps = connection.prepareStatement("SELECT * FROM emails WHERE email=?");
        ps.setString(1, email);
        ResultSet rs = ps.executeQuery();
        
        if (rs.next()) {
            //Email exists
            CallableStatement cs = connection.prepareCall("{call unsubscribeEmail(?)}");
            cs.setString(1, email);
            int status = cs.executeUpdate();
            
            if (status == 1) {
                System.out.println("Email unsubscribed successfully.");
            } else {
                System.out.println("Error occurred while trying to unsubscribe email.");
            }
        } else {
            //Email does not exist
            System.out.println("This email does not exist in our database.");
        }
        
    }
}