import java.sql.*;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class post extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");
        insert_user_message_in_db(name, message);
        response.sendRedirect("/index.html");
    }

    private static void insert_user_message_in_db(String name, String message) {
        try {
            Connection conn = DriverManager.getConnection("jdbc:sqlite:test.db");
            Statement statement = conn.createStatement();
            ResultSet results = statement.executeQuery("INSERT INTO messages (name, message) VALUES (" + name + ", " + message + ");");
            statement.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}