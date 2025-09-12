import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "UserServlet", value = {"/login", "/do_login", "/user_page", "/admin_page"})
public class UserServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        
        if (path.equals("/login")) {
            login(request, response);
        } else if (path.equals("/user_page")) {
            userPage(request, response);
        } else if (path.equals("/admin_page")) {
            adminPage(request, response);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        
        if (path.equals("/do_login")) {
            doLogin(request, response);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /login
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle POST /do_login
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            response.sendRedirect(request.getContextPath() + "/admin_page");
        } else {
            response.sendRedirect(request.getContextPath() + "/user_page");
        }
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /user_page
        request.getRequestDispatcher("/WEB-INF/views/user_page.jsp").forward(request, response);
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /admin_page
        request.getRequestDispatcher("/WEB-INF/views/admin_page.jsp").forward(request, response);
    }
}