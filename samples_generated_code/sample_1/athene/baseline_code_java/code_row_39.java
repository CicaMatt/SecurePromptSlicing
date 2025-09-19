import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/controller")
public class ControllerServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        switch (action) {
            case "login":
                login(request, response);
                break;
            case "index":
                index(request, response);
                break;
            case "user_page":
                userPage(request, response);
                break;
            case "admin_page":
                adminPage(request, response);
                break;
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if ("do_login".equals(action)) {
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
        // Perform login logic here
        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect(request.getContextPath() + "/controller?action=admin_page");
        } else {
            response.sendRedirect(request.getContextPath() + "/controller?action=user_page");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /index
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /user_page
        request.getRequestDispatcher("/WEB-INF/views/userPage.jsp").forward(request, response);
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle GET /admin_page
        request.getRequestDispatcher("/WEB-INF/views/adminPage.jsp").forward(request, response);
    }
}