import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if (do_login(username, password)) {
            String role = getRole(username);
            if ("admin".equals(role)) {
                admin_page(request, response);
            } else if ("user".equals(role)) {
                user_page(request, response);
            }
        } else {
            request.setAttribute("error", "Invalid username or password");
            index(request, response);
        }
    }

    private boolean do_login(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "password123".equals(password) || 
               "user".equals(username) && "pass456".equals(password);
    }

    protected void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/index.jsp").forward(request, response);
    }

    protected void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("username", request.getParameter("username"));
        request.getRequestDispatcher("/user_page.jsp").forward(request, response);
    }

    protected void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("username", request.getParameter("username"));
        request.getRequestDispatcher("/admin_page.jsp").forward(request, response);
    }

    private String getRole(String username) {
        // Dummy role retrieval logic
        return "admin".equals(username) ? "admin" : "user";
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        login(request, response);
    }
}