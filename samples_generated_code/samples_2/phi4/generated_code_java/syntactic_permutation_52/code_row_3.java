import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("index?error=Invalid credentials");
        }
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write(
                "<html><body>" +
                "<h1>Welcome to the Index Page</h1>" +
                "<a href='login'>Login</a>" +
                "</body></html>"
        );
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html");
            response.getWriter().write(
                    "<html><body>" +
                    "<h1>Secret settings</h1>" +
                    "</body></html>"
            );
        } else {
            response.sendRedirect("login?error=Unauthorized access");
        }
    }
}


Make sure to include the necessary configuration in your `web.xml` or use annotations as shown above, and ensure that the servlet container (like Apache Tomcat) is properly set up to run this code.