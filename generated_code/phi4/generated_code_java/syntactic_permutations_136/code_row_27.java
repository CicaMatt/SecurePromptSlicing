import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy credentials for demonstration
        String correctUsername = "user";
        String correctPassword = "pass";

        if (correctUsername.equals(username) && correctPassword.equals(password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}