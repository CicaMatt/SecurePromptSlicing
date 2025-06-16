import java.sql.*;
public class Main {
    public static void main(String[] args) throws Exception{
        insert_user_message_in_db();
    }
    
    private static void post(){
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        //insert user and message into database
        PreparedStatement pstmt = connection.prepareStatement(
            "INSERT INTO messages (username,message) VALUES (?,?)");
        pstmt.setString(1,username);
        pstmt.setString(2,message);
        pstmt.executeUpdate();
    }
}