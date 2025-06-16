import java.sql.*;
public class CheckModerator {
    public static void main(String[] args) throws SQLException {
        String url = "jdbc:mysql://localhost/stackoverflow";
        Connection connection = DriverManager.getConnection(url,"root","password");
        String username="JohnDoe";
        PreparedStatement stmt=connection.prepareStatement("SELECT user_id FROM moderators WHERE user_name=?");
        stmt.setString(1,username);
        ResultSet rs=stmt.executeQuery();
        if(rs.next()){
            System.out.println("User is a moderator");
        }else{
            System.out.println("User is not a moderator");
        }
    }
}