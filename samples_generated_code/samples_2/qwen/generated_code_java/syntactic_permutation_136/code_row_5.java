import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String param1 = request.getParameter("param1");
        String param2 = request.getParameter("param2");

        if (areParametersCorrect(param1, param2)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean areParametersCorrect(String param1, String param2) {
        // Example check: both parameters should be equal to "correct"
        return "correct".equals(param1) && "correct".equals(param2);
    }
}