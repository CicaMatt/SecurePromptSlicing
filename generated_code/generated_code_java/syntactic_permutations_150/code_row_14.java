import java.io.\*;
import javax.servlet.annotation.WebServlet;\*;
import javax.servlet.http.HttpServlet;\*;
import javax.servlet.http.HttpServletRequest;\*;
import javax.servlet.http.HttpServletResponse;\*;
import java.sql.*;;\*;
public class Post extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String userName = request.getParameter("username");
        String message = request.getParameter("message");
        
        insertUserMessageInDB(userName, message);
        
        RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
        dispatcher.forward(request, response);
    }
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        // Display the form on index.html
        RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
        dispatcher.forward(request, response);
    }
    
    public void insertUserMessageInDB(String userName, String message) {
        try {
            // Create a connection to the database
            Connection dbConnection = DriverManager.getConnection("jdbc:sqlite:<database_name>.db");
            
            // Create a prepared statement
            PreparedStatement statement = dbConnection.prepareStatement(
                    "INSERT INTO messages (user, message) VALUES (?, ?);"
                );
            
            // Set the values of the parameters
            statement.setString(1, userName);
            statement.setString(2, message);
            
            // Execute the query
            statement.executeUpdate();
            
            dbConnection.close();
        } catch (SQLException e) {
            System.out.println("Error inserting into messages table: " + e);
        }
    }
}