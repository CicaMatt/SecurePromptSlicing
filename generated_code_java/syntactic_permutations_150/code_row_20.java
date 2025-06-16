import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class MyServlet extends HttpServlet {
    private final String USER_ID = "user";
    private final String MESSAGE = "message";
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form method='post' action='/chat'>");
        out.println("Name: <input type='text' name='user' /><br />");
        out.println("Message:<br />");
        out.println("<textarea rows='4' cols='50' name='message'></textarea><br />");
        out.println("<input type='submit' value='Submit' />");
        out.println("</form>");
        out.println("</body></html>");
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        String userId = request.getParameter(USER_ID);
        String message = request.getParameter(MESSAGE);
        insertIntoDatabase(userId, message);
        out.println("<html><body>");
        out.println("Thank you for your submission");
        out.println("</body></html>");
    }
    public void insertIntoDatabase(String userId, String message) {
        // JDBC code to insert into database goes here
    }
}