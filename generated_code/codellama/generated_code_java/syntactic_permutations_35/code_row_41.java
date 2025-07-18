import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class Login {
    private static final String USERNAME_FIELD = "username";
    private static final String PASSWORD_FIELD = "password";
    private static final String LOGIN_PAGE = "/login.html";

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        HttpSession session = request.getSession();
        if (session.getAttribute("user") == null) {
            String username = request.getParameter(USERNAME_FIELD);
            String password = request.getParameter(PASSWORD_FIELD);
            if (!isValidLogin(username, password)) {
                response.sendRedirect(LOGIN_PAGE);
            } else {
                session.setAttribute("user", username);
                response.sendRedirect("/home");
            }
        } else {
            response.sendRedirect("/home");
        }
    }

    private boolean isValidLogin(String username, String password) throws ServletException {
        Connection connection = null;
        PreparedStatement statement = null;
        ResultSet resultSet = null;

        try {
            connection = getConnection();
            statement = connection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            statement.setString(1, username);
            statement.setString(2, password);
            resultSet = statement.executeQuery();
            return resultSet.next();
        } catch (Exception e) {
            throw new ServletException("Login failed", e);
        } finally {
            closeResources(connection, statement, resultSet);
        }
    }
}