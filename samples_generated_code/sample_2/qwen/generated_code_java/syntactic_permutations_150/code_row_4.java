import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insertUserMessageInDB(username, message);
        response.sendRedirect("index.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Implement database insertion logic here
        System.out.println("Inserting into DB: " + username + ", " + message);
    }
}
