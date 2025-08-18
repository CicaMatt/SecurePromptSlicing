import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is required.");
            return;
        }

        try {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE email = ?");
            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                PreparedStatement deleteStatement = connection.prepareStatement("DELETE FROM users WHERE email = ?");
                deleteStatement.setString(1, email);
                deleteStatement.executeUpdate();
                response.getWriter().write("User has been unsubscribed successfully.");
            } else {
                response.getWriter().write("User is not subscribed.");
            }

            resultSet.close();
            statement.close();
            connection.close();
        } catch (Exception e) {
            response.getWriter().write("An error occurred: " + e.getMessage());
        }
    }
}