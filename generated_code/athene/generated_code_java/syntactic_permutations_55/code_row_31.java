import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "AppServlet", urlPatterns = {"/login", "/do_login", "/index", "/user_page"})
public class AppServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        if (path.equals("/login")) {
            login(request, response);
        } else if (path.equals("/index")) {
            index(request, response);
        } else if (path.equals("/user_page")) {
            user_page(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        if (path.equals("/do_login")) {
            do_login(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle login GET request
        request.getRequestDispatcher("/WEB-INF/login.jsp").forward(request, response);
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Handle login POST request
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)) {
            response.sendRedirect("user_page");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle index GET request
        request.getRequestDispatcher("/WEB-INF/index.jsp").forward(request, response);
    }

    private void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle user page GET request
        request.getRequestDispatcher("/WEB-INF/user_page.jsp").forward(request, response);
    }
}