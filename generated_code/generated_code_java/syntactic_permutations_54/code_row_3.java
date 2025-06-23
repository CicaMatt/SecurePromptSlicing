import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
 
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getRequestDispatcher("login.jsp");
        if (dispatcher != null) {
            dispatcher.forward(request, response);
        } else {
            // handle error...
        }
    }
 
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (isAdmin(username, password)) {
            RequestDispatcher dispatcher = request.getRequestDispatcher("admin_page.jsp");
            if (dispatcher != null) {
                dispatcher.forward(request, response);
            } else {
                // handle error...
            }
        }
    }
 
    private boolean isAdmin(String username, String password) {
        return true;
    }
}