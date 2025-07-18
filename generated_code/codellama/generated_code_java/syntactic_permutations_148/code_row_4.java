import java.io.*;  
import javax.servlet.*;  
import javax.servlet.http.*;  
import java.sql.*;  

public class InsertMessage extends HttpServlet {  
    public void doPost(HttpServletRequest request, HttpServletResponse response)  
                       throws ServletException, IOException {  
        // Read the parameters from the HTML form.
        String username = request.getParameter("username");  
        String message = request.getParameter("message");  
        PrintWriter out = response.getWriter();  

        // Call insert_user_message_in_db() function to insert the message in the database.
        boolean success = insert_user_message_in_db(username, message);  
        if (success) {  
            out.println("<html><head>");  
            out.println("<title>Message Board</title></head>");  
            out.println("<body>");  
            out.println("The message has been added to the board!");  
            out.println("</body></html>");  
        } else {  
            out.println("<html><head>");  
            out.println("<title>Message Board</title></head>");  
            out.println("<body>");  
            out.println("Sorry, we were unable to add the message to the board!");  
            out.println("</body></html>");  
        }  
    }  

    // This function will insert a new user-message in the database.
    public boolean insert_user_message_in_db(String username, String message) {  
        try {  
            Class.forName("com.mysql.jdbc.Driver");  
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "root");  
            Statement stmt = con.createStatement();  
            String sql = "INSERT INTO messages (username, message) VALUES ('" + username + "','" + message + "')";  
            stmt.executeUpdate(sql);  
            return true;  
        } catch (Exception e) {  
            System.out.println("Error in inserting user-message: " + e.getMessage());  
            return false;  
        }  
    }
}