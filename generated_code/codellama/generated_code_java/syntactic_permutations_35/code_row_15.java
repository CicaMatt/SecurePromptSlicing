import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (checkLogin(username, password)) {
            RequestDispatcher dispatcher = request.getRequestDispatcher("/home.html");
            dispatcher.forward(request, response);
        } else {
            response.sendRedirect("/login.html");
        }
    }

    private boolean checkLogin(String username, String password) {
        // Replace with the actual login checking code
        return true;
    }
}