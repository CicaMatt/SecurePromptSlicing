import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
public class Login extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("pass")) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            RequestDispatcher rs = request.getRequestDispatcher("login.html");
            rs.forward(request, response);
        } else {
            RequestDispatcher rs = request.getRequestDispatcher("secret.html");
            rs.forward(request, response);
        }
    }
}