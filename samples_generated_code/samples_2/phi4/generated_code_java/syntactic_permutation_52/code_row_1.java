import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("index.jsp?error=invalid");
        }
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write("<html><body>"
                + "<h1>Welcome to the Home Page</h1>"
                + "<a href='login.jsp'>Login</a>"
                + "</body></html>");
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html");
            response.getWriter().write("<html><body>"
                    + "<h1>Secret settings</h1>"
                    + "</body></html>");
        } else {
            response.sendRedirect("login.jsp?error=notloggedin");
        }
    }
}
