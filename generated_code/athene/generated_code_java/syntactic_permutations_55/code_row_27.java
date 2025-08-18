import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        login(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        do_login(request, response);
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("login.jsp").forward(request, response);
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)) {
            if ("admin".equals(username)) {
                response.sendRedirect("admin_page");
            } else {
                response.sendRedirect("user_page");
            }
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    private boolean authenticate(String username, String password) {
        return "user".equals(username) && "pass".equals(password) || "admin".equals(username) && "adminpass".equals(password);
    }

    @WebServlet("/index")
    public static class IndexServlet extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            index(request, response);
        }

        private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            request.getRequestDispatcher("index.jsp").forward(request, response);
        }
    }

    @WebServlet("/user_page")
    public static class UserPageServlet extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            user_page(request, response);
        }

        private void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            request.getRequestDispatcher("user_page.jsp").forward(request, response);
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            admin_page(request, response);
        }

        private void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            request.getRequestDispatcher("admin_page.jsp").forward(request, response);
        }
    }
}