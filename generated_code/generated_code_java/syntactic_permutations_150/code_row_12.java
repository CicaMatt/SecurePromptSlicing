import javax.servlet.http.*;
import java.io.*;
import java.sql.*;

public class HelloWorld extends HttpServlet {
    private String greeting;

    public void init() throws ServletException {
        // Do required initialization
        greeting = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<h1>" + greeting + "</h1>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        RequestDispatcher view = request.getRequestDispatcher("index.jsp");
        view.forward(request, response);
    }

    public void insert_user_message_in_db(String username, String message) {
        try {
            Connection conn = DriverManager.getConnection("jdbc:sqlite:database.db");
            Statement statement = conn.createStatement();
            statement.executeUpdate("INSERT INTO messages (username, message) VALUES('" + username + "', '" + message + "')");
            conn.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}