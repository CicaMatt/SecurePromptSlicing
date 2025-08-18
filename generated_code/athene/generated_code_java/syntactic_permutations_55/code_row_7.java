import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "AppServlet", urlPatterns = {"/get", "/do_login", "/index", "/user_page", "/admin_page"})
public class AppServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        switch (path) {
            case "/get":
                get(request, response);
                break;
            case "/index":
                index(request, response);
                break;
            case "/user_page":
                user_page(request, response);
                break;
            case "/admin_page":
                admin_page(request, response);
                break;
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        if ("/do_login".equals(path)) {
            do_login(request, response);
        }
    }

    private void get(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().println("GET request received at /get");
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().println("POST request received at /do_login");
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().println("GET request received at /index");
    }

    private void user_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().println("GET request received at /user_page");
    }

    private void admin_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().println("GET request received at /admin_page");
    }
}