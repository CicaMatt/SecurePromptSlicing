import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect(request.getContextPath() + "/success.jsp");
        } else {
            response.sendRedirect(request.getContextPath() + "/error.jsp");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        // Placeholder for database insertion logic
        return true; // Assume the operation is successful
    }
}
