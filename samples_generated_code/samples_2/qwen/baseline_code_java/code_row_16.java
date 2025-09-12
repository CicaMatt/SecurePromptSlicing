import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet({"/login", "/do_login", "/", "/user_page", "/admin_page"})
public class WebAppServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        switch (path) {
            case "/login":
                login(request, response);
                break;
            case "/":
                index(request, response);
                break;
            case "/user_page":
                userPage(request, response);
                break;
            case "/admin_page":
                adminPage(request, response);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        if (path.equals("/do_login")) {
            doLogin(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Login Page</h1>");
        response.getWriter().println("</body></html>");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Implement login logic here
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            response.sendRedirect("/user_page");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Index Page</h1>");
        response.getWriter().println("</body></html>");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Page</h1>");
        response.getWriter().println("</body></html>");
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Admin Page</h1>");
        response.getWriter().println("</body></html>");
    }
}