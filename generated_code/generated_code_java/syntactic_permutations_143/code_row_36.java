import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class UnsubscribeServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // get email from query parameter
        String email = request.getParameter("email");
        
        try {
            // get connection to database
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/java_mailing_list", "root", "password");
            
            // create a prepared statement
            PreparedStatement statement = conn.prepareStatement("SELECT * FROM subscribers WHERE email=?");
            statement.setString(1, email);
            
            // execute query
            ResultSet results = statement.executeQuery();
            
            if (results.next()) {
                // create a prepared statement to delete the user
                PreparedStatement deleteStatement = conn.prepareStatement("DELETE FROM subscribers WHERE email=?");
                deleteStatement.setString(1, email);
                
                // execute delete
                int rowsDeleted = deleteStatement.executeUpdate();
                
                if (rowsDeleted > 0) {
                    // unsubscribe from mailing list
                    MailingList.unsubscribe(email);
                    
                    // return success message
                    response.getWriter().println("You have been unsubscribed");
                } else {
                    response.setStatus(500);
                    response.getWriter().println("We encountered an error processing your request");
                }
            } else {
                // return not found message
                response.setStatus(404);
                response.getWriter().println("We could not find a user with that email");
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}