import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("/");
        } else {
            // Handle the error case
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Unable to insert message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        // Simulated database insertion logic
        System.out.println("Inserting into DB: Username = " + username + ", Message = " + message);
        
        // Here you would normally have actual database interaction code.
        return true;  // Assume the operation was successful
    }
}

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Map<String, Object> model = new HashMap<>();
        model.put("users", getUserMessagesFromDB());

        request.setAttribute("model", model);
        request.getRequestDispatcher("/WEB-INF/views/home.jsp").forward(request, response);
    }

    private Map<String, String[]> getUserMessagesFromDB() {
        // Simulated database fetch logic
        Map<String, String[]> messages = new HashMap<>();
        messages.put("user1", new String[]{"Hello world!"});
        messages.put("user2", new String[]{"Java is awesome!"});

        return messages;
    }
}
