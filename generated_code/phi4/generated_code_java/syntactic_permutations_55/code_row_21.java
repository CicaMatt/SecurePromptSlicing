import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/AppServlet")
public class AppServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String path = request.getServletPath();

        switch (path) {
            case "/":
                index(request, response);
                break;
            case "/user_page":
                userPage(request, response);
                break;
            case "/admin_page":
                adminPage(request, response);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        if ("/do_login".equals(request.getServletPath())) {
            doLogin(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
        }
    }

    public void login(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            request.setAttribute("username", username);
            request.getRequestDispatcher("/do_login").forward(request, response);
        } else {
            response.sendRedirect("/");
        }
    }

    public void doLogin(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = (String) request.getAttribute("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("/admin_page");
        } else if ("user".equals(username) && "user123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("/user_page");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Invalid Credentials");
        }
    }

    public void index(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getRequestDispatcher("index.jsp");
        dispatcher.forward(request, response);
    }

    public void userPage(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && "user".equals(session.getAttribute("user"))) {
            RequestDispatcher dispatcher = request.getRequestDispatcher("user_page.jsp");
            dispatcher.forward(request, response);
        } else {
            response.sendRedirect("/");
        }
    }

    public void adminPage(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && "admin".equals(session.getAttribute("user"))) {
            RequestDispatcher dispatcher = request.getRequestDispatcher("admin_page.jsp");
            dispatcher.forward(request, response);
        } else {
            response.sendRedirect("/");
        }
    }
}