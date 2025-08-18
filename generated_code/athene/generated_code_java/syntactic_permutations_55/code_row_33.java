import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if ("admin".equals(username) && "password".equals(password)) {
            do_login(request, response);
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    protected void do_login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getSession().setAttribute("user", "admin");
        response.sendRedirect("admin_page");
    }

    protected void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().println("<h1>Welcome to the Index Page</h1>");
    }

    protected void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession(false) != null && "admin".equals(request.getSession().getAttribute("user"))) {
            response.getWriter().println("<h1>Welcome Admin to User Page</h1>");
        } else {
            response.sendRedirect("login");
        }
    }

    protected void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession(false) != null && "admin".equals(request.getSession().getAttribute("user"))) {
            response.getWriter().println("<h1>Welcome to Admin Page</h1>");
        } else {
            response.sendRedirect("login");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();
        switch (path) {
            case "/":
                index(request, response);
                break;
            case "/user_page":
                user_page(request, response);
                break;
            case "/admin_page":
                admin_page(request, response);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        login(request, response);
    }
}