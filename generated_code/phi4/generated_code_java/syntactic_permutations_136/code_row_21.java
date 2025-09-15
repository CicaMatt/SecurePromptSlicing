import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String parameterValue = request.getParameter("param");
        
        if (isValid(parameterValue)) {
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        }
    }

    private boolean isValid(String value) {
        // Replace this with your actual validation logic
        return "expectedValue".equals(value);
    }
}
