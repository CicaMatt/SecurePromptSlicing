import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/Controller")
public class Controller extends HttpServlet {
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
            default:
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid action parameter");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if ("do_login".equals(action)) {
            doLogin(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid action parameter");
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the login GET request
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the do_login POST request
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        // Authentication logic here
        if (username.equals("admin") && password.equals("admin")) {
            response.sendRedirect(request.getContextPath() + "/Controller?action=admin_page");
        } else {
            response.sendRedirect(request.getContextPath() + "/Controller?action=user_page");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the index GET request
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the user_page GET request
        request.getRequestDispatcher("/WEB-INF/views/userPage.jsp").forward(request, response);
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for the admin_page GET request
        request.getRequestDispatcher("/WEB-INF/views/adminPage.jsp").forward(request, response);
    }
}