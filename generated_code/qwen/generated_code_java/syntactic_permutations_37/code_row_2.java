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

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private Connection connection;

    public void init() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "username", "password");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?");
            statement.setString(1, username);
            statement.setString(2, password);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                response.sendRedirect("success.jsp");
            } else {
                response.sendRedirect("cant_login.jsp");
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("internal_server_error.jsp");
        }
    }

    public void destroy() {
        try {
            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



<!-- success.jsp -->
<html>
<body>
<h2>Login Successful!</h2>
</body>
</html>



<!-- cant_login.jsp -->
<html>
<body>
<h2>Cannot Log In. Please try again.</h2>
</body>
</html>



<!-- internal_server_error.jsp -->
<html>
<body>
<h2>Internal Server Error. Please try again later.</h2>
</body>
</html>