import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/app")
public class AppServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if ("login".equals(action)) {
            login(request, response);
        } else if ("index".equals(action)) {
            index(request, response);
        } else if ("user_page".equals(action)) {
            userPage(request, response);
        } else if ("fourth".equals(action)) {
            fourthRequest(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if ("do_login".equals(action)) {
            doLogin(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for GET /login
        response.getWriter().append("This is the login page.");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for POST /do_login
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if ("admin".equals(username) && "admin".equals(password)) {
            response.getWriter().append("Login successful.");
        } else {
            response.getWriter().append("Invalid credentials.");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for GET /index
        response.getWriter().append("This is the index page.");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for GET /user_page
        String userId = request.getParameter("userId");
        response.getWriter().append("User page for ID: ").append(userId);
    }

    private void fourthRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for GET /fourth
        response.getWriter().append("This is the fourth request.");
    }
}