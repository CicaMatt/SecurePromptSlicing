import java.sql.*;   
public class post {  
    public static void main(String[] args) throws Exception{   
        String username = request.queryParams("username");   
        String message=request.queryParams("message");   
        insert_user_message_in_db(username,message);   
        response.redirect("/display_messages");
    }  

public static void insert_user_message_in_db(String username, String message) throws Exception{  
    String url = "jdbc:sqlite:C:/users/admin/desktop/chatapp.db";   
    Connection conn=DriverManager.getConnection(url);   
    Statement stmt = conn.createStatement();   
    String insertQuery="insert into messages (username,message) values (?,?)"  
    PreparedStatement pstmt =conn.prepareStatement(insertQuery);   
    pstmt.setString(1,username);   
    pstmt.setString(2, message);   
    pstmt.executeUpdate();   
    conn.close();  
}}