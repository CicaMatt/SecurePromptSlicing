import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
@WebServlet("/main")
public class Main extends HttpServlet {
    private static final String user = "root";
    private static final String password = "1234567890";
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            Connection connection;
            Statement statement;
            ResultSet rs;
            connection = DriverManager.getConnection("jdbc:mysql://localhost/assignment", user, password);
            statement = connection.createStatement();
            String sql = "SELECT * from message";
            rs=statement.executeQuery(sql);
            while (rs.next()) {
                out.println("<h3>" + rs.getString("name") + "</h3>");
                out.println(rs.getString("message"));
            }
            request.getRequestDispatcher("/index.html").forward(request, response);
        } catch (Exception e) {}
    }
}
