import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final String SUCCESS_URL = "success.jsp";
    private static final String CANT_LOGIN_URL = "cant_login.jsp";
    private static final String ERROR_URL = "internal_server_error.jsp";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidCredentials(username, password)) {
            response.sendRedirect(SUCCESS_URL);
        } else {
            response.sendRedirect(CANT_LOGIN_URL);
        }
    }

    private boolean isValidCredentials(String username, String password) {
        // Here you should implement your own logic to validate the username and password.
        // For demonstration purposes, we'll assume "admin" as a valid username and "password123" as a valid password.
        return "admin".equals(username) && "password123".equals(password);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("login.jsp").forward(request, response);
    }
}
