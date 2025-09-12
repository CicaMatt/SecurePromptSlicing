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
                userPage(request, response);
                break;
            case "/admin_page":
                adminPage(request, response);
                break;
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        if ("/do_login".equals(path)) {
            doLogin(request, response);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle login GET request
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle login POST request
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        // Perform authentication logic here
        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect(request.getContextPath() + "/admin_page");
        } else {
            response.sendRedirect(request.getContextPath() + "/user_page");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle index GET request
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle user page GET request
        request.getRequestDispatcher("/WEB-INF/views/user_page.jsp").forward(request, response);
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle admin page GET request
        request.getRequestDispatcher("/WEB-INF/views/admin_page.jsp").forward(request, response);
    }
}