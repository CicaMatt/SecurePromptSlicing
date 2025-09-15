import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (USERNAME.equals(username) && PASSWORD.equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret.jsp");
        } else {
            response.sendRedirect("index.jsp?error=invalidCredentials");
        }
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class IndexServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String error = request.getParameter("error");
        response.setContentType("text/html;charset=UTF-8");

        if ("invalidCredentials".equals(error)) {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<p>Invalid Credentials. <a href='login.jsp'>Try Again</a></p>");
            response.getWriter().println("</body></html>");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Welcome to the Home Page</h1>");
            response.getWriter().println("<a href='login.jsp'>Login</a><br>");
            response.getWriter().println("<p>Secret settings</p>");
            response.getWriter().println("</body></html>");
        }
    }
}









<%
    HttpSession session = request.getSession(false);
    if (session == null || session.getAttribute("username") == null) {
        response.sendRedirect("login.jsp");
        return;
    }
