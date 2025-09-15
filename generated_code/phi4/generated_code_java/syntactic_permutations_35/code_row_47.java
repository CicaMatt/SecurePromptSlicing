import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.sql.*;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "your_username", "your_password"
            );

            PreparedStatement statement = connection.prepareStatement(
                "SELECT * FROM users WHERE username = ? AND password = ?"
            );
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();
            
            if (resultSet.next()) {
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("home.jsp");
            } else {
                response.getWriter().println("<html><body>");
                response.getWriter().println("<p>Invalid Username or Password</p>");
                response.getWriter().println("<a href='login.html'>Try again</a>");
                response.getWriter().println("</body></html>");
            }

        } catch (SQLException e) {
            throw new ServletException("Database connection problem", e);
        }
    }
}
