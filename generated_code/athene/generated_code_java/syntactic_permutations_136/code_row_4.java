import javax.servlet.http.HttpServletRequest;
import javax.servlet.annotation.WebServlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import java.io.IOException;

@WebServlet("/check_mod")
public class ModCheckerServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "secret".equals(password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }
}