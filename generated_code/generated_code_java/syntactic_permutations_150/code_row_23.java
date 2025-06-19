import java.sql.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
 
@WebServlet("/main_page")
public class MainPage extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Set the response message's MIME type
        response.setContentType("text/html;charset=UTF-8");
        
        // Get a output writer to write the response message into the network socket
        PrintWriter out = response.getWriter();
 
        // Write the response message, in an HTML page
        try {
            out.println("<!doctype html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">");
            out.println("<title>A Simple Chat Room</title>");
            out.println("</head>");
            out.println("<body>");
            
            // Write the form that allows user to submit a message
            out.println("<form action=\"/chat_room/post\" method=\"post\">");
            out.println("<input type=\"text\" name=\"username\"><br>");
            out.println("<textarea rows=\"4\" cols=\"50\" name=\"message\"></textarea><br>");
            out.println("<input type=\"submit\" value=\"Post\">");
            out.println("</form>");
            
            // Write a list that displays the 10 latest messages, newest first
            out.println("<ul>");
            Connection conn = getConnection();
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM MESSAGES ORDER BY ID DESC LIMIT 10");
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                out.println("<li>" + rs.getString("USERNAME") + ": " + rs.getString("MESSAGE") + "</li>");
            }
            conn.close();
            
            out.println("</ul>");
            out.println("</body>");
            out.println("</html>");
        } catch (SQLException ex) {
            System.err.println(ex);
        } finally {
            if (out != null) {
                out.close();
            }
        }
    }
 
    // This method gets a database connection from the Cloud SQL instance.
    private Connection getConnection() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.jdbc.GoogleDriver");
        String url = System.getProperty("cloudsql");
        return DriverManager.getConnection(url);
    }
}