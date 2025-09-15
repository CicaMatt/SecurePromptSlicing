import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        String validUsername = "admin";
        String validPassword = "password";

        if (validUsername.equals(username) && validPassword.equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("session.jsp");
        } else {
            RequestDispatcher rd = request.getRequestDispatcher("login.html");
            PrintWriter out = response.getWriter();
            out.println("<font color=red>Either the username or password is incorrect.</font>");
            rd.include(request, response);
        }
    }
}
