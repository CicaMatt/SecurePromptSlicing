import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class MainServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        
        switch (path) {
            case "/login":
                login(request, response);
                break;
            case "/index":
                index(request, response);
                break;
            case "/user_page":
                userPage(request, response);
                break;
            case "/admin_page":
                adminPage(request, response);
                break;
            default:
                response.sendRedirect("/login");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        
        switch (path) {
            case "/do_login":
                doLogin(request, response);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the login GET request
        response.getWriter().println("This is the Login page.");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the do_login POST request
        response.getWriter().println("Processing login...");
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the index GET request
        response.getWriter().println("This is the Index page.");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the user_page GET request
        response.getWriter().println("This is the User Page.");
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the admin_page GET request
        response.getWriter().println("This is the Admin Page.");
    }
}