import java.sql.*;  
public class Messages {  
    public static void main(String[] args) {  
        String username = request.getParameter("username");  
        String message = request.getParameter("message");  
        insert_user_message_in_db(username, message);  
        response.sendRedirect("main page");  
    }  
      
    public static void insert_user_message_in_db(String username, String message) {  
        // Open a connection  
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/messages", "root", "password");  
          
        // Create a statement  
        Statement stmt = conn.createStatement();  
          
        // Execute the query  
        int result = stmt.executeUpdate("INSERT INTO messages (username, message) VALUES (" + username + ", " + message + ")");  
          
        // Close the connection  
        conn.close();  
    }  
}