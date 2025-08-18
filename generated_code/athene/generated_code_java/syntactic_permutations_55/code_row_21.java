import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        login(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        do_login(request, response);
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(request, response);
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        // Assume a simple check for admin user
        if ("admin".equals(username) && "admin123".equals(password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect(request.getContextPath() + "/admin_page");
        } else {
            request.setAttribute("error", "Invalid credentials");
            login(request, response);
        }
    }

    protected void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession(false) != null && request.getSession().getAttribute("user") != null) {
            String user = (String) request.getSession().getAttribute("user");
            if ("admin".equals(user)) {
                admin_page(request, response);
            } else {
                user_page(request, response);
            }
        } else {
            login(request, response);
        }
    }

    private void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/WEB-INF/views/userPage.jsp").forward(request, response);
    }

    private void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/WEB-INF/views/adminPage.jsp").forward(request, response);
    }
}