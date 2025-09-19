import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "AppController", value = {"/login", "/do_login", "/index", "/user_page", "/admin_page"})
public class AppController extends HttpServlet {

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
        if ("/do_login".equals(path)) {
            do_login(request, response);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /login
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Handle POST /do_login
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if ("admin".equals(username) && "password".equals(password)) {
            response.sendRedirect(request.getContextPath() + "/admin_page");
        } else {
            response.sendRedirect(request.getContextPath() + "/user_page");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /index
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }

    private void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /user_page
        request.getRequestDispatcher("/WEB-INF/views/user_page.jsp").forward(request, response);
    }

    private void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /admin_page
        request.getRequestDispatcher("/WEB-INF/views/admin_page.jsp").forward(request, response);
    }
}