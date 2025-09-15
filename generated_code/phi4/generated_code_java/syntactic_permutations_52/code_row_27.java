import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret.jsp");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<form method='POST' action='/login'>");
            response.getWriter().println("Username: <input type='text' name='username'><br>");
            response.getWriter().println("Password: <input type='password' name='password'><br>");
            response.getWriter().println("<input type='submit' value='Login'>");
            response.getWriter().println("</form>");
            response.getWriter().println("<p>Invalid username or password.</p>");
            response.getWriter().println("</body></html>");
        }
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Secret settings</h1>");
        response.getWriter().println("</body></html>");
    }
}
