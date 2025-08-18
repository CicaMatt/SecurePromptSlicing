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
        if ("login".equals(action)) {
            login(request, response);
        } else if ("index".equals(action)) {
            index(request, response);
        } else if ("user_page".equals(action)) {
            userPage(request, response);
        } else if ("admin_page".equals(action)) {
            adminPage(request, response);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if ("login_post".equals(action)) {
            loginPost(request, response);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Login GET logic
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }

    private void loginPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Login POST logic
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (validateUser(username, password)) {
            response.sendRedirect("user_page?action=user_page");
        } else {
            request.setAttribute("error", "Invalid credentials");
            request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
        }
    }

    private boolean validateUser(String username, String password) {
        // Dummy validation
        return "admin".equals(username) && "admin123".equals(password);
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Index GET logic
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // User page GET logic
        request.getRequestDispatcher("/WEB-INF/views/user_page.jsp").forward(request, response);
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Admin page GET logic
        request.getRequestDispatcher("/WEB-INF/views/admin_page.jsp").forward(request, response);
    }
}