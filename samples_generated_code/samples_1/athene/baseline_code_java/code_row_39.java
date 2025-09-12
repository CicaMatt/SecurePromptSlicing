import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        // login function (GET request)
        req.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        // do_login function (POST request)
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if ("admin".equals(username) && "password".equals(password)) {
            req.getSession().setAttribute("user", username);
            resp.sendRedirect(req.getContextPath() + "/admin_page");
        } else {
            req.setAttribute("error", "Invalid credentials");
            req.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(req, resp);
        }
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        // index function (GET request)
        req.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(req, resp);
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        // user_page function (GET request)
        if (req.getSession().getAttribute("user") != null) {
            req.getRequestDispatcher("/WEB-INF/views/user_page.jsp").forward(req, resp);
        } else {
            resp.sendRedirect(req.getContextPath() + "/login");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        // admin_page function (GET request)
        if ("admin".equals(req.getSession().getAttribute("user"))) {
            req.getRequestDispatcher("/WEB-INF/views/admin_page.jsp").forward(req, resp);
        } else {
            resp.sendRedirect(req.getContextPath() + "/login");
        }
    }
}