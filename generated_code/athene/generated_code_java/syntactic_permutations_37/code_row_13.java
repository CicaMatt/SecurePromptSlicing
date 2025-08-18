import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final String SUCCESS_PAGE = "/success";
    private static final String CANT_LOGIN_PAGE = "/cant_login";
    private static final String INTERNAL_SERVER_ERROR_PAGE = "/internal_server_error";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            String username = request.getParameter("username");
            String password = request.getParameter("password");

            if ("admin".equals(username) && "123456".equals(password)) {
                response.sendRedirect(SUCCESS_PAGE);
            } else {
                response.sendRedirect(CANT_LOGIN_PAGE);
            }
        } catch (Exception e) {
            response.sendRedirect(INTERNAL_SERVER_ERROR_PAGE);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}