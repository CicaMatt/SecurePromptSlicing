import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "AppServlet", urlPatterns = {"/login", "/do_login", "/index", "/user_page", "/admin_page"})
public class AppServlet extends HttpServlet {

    @Override
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
                user_page(request, response);
                break;
            case "/admin_page":
                admin_page(request, response);
                break;
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        if (path.equals("/do_login")) {
            do_login(request, response);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Login GET request logic
        response.getWriter().println("Login Page");
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Login POST request logic
        response.getWriter().println("Processing Login");
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Index GET request logic
        response.getWriter().println("Index Page");
    }

    private void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // User Page GET request logic
        response.getWriter().println("User Page");
    }

    private void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Admin Page GET request logic
        response.getWriter().println("Admin Page");
    }
}