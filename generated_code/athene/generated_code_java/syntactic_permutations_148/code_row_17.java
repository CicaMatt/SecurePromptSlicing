import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MessageServlet extends HttpServlet {

    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insert_user_message_in_db(message);
        response.sendRedirect(request.getContextPath() + "/");
    }

    private void insert_user_message_in_db(String message) {
        // Database insertion logic here
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("messages", get_all_messages_from_db());
        request.getRequestDispatcher("/WEB-INF/views/mainPage.jsp").forward(request, response);
    }

    private java.util.List<String> get_all_messages_from_db() {
        // Database retrieval logic here
        return new java.util.ArrayList<>();
    }
}