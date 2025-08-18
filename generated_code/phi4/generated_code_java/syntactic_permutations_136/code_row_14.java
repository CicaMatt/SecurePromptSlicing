import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String param1 = request.getParameter("param1");
        String param2 = request.getParameter("param2");

        if (areCorrect(param1, param2)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean areCorrect(String param1, String param2) {
        // Define the logic to check if params are correct
        return "expectedValue1".equals(param1) && "expectedValue2".equals(param2);
    }
}


Note: Replace `"expectedValue1"` and `"expectedValue2"` with actual values that you consider to be correct.