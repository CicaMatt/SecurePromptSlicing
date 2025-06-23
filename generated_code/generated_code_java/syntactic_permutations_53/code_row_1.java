import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class Redirect extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Check if user is logged in
        if (username != null && password != null) {
            if (isAdmin(username)) {
                RequestDispatcher dispatcher = request.getRequestDispatcher("/admin");
                dispatcher.forward(request, response);
            } else {
                RequestDispatcher dispatcher = request.getRequestDispatcher("/user");
                dispatcher.forward(request, response);
            }
        }

        // User is not logged in
        else {
            RequestDispatcher dispatcher = request.getRequestDispatcher("/login");
            dispatcher.forward(request, response);
        }
    }

    public boolean isAdmin(String username) {
        // Check if user is admin
        return true;
    }
}