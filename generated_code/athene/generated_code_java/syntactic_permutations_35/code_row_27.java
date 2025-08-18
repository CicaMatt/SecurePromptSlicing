import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidUser(username, password)) {
            RequestDispatcher dispatcher = request.getRequestDispatcher("/home.html");
            dispatcher.forward(request, response);
        } else {
            response.sendRedirect("login.html?error=1");
        }
    }

    private boolean isValidUser(String username, String password) {
        // Dummy user data for demonstration
        return "admin".equals(username) && "password".equals(password);
    }
}