import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insert_user_message_in_db(message);
        response.sendRedirect("main");
    }

    private void insert_user_message_in_db(String message) {
        // Code to insert the message into the database
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("messages", get_all_messages_from_db());
        request.getRequestDispatcher("/WEB-INF/views/main.jsp").forward(request, response);
    }

    private java.util.List<String> get_all_messages_from_db() {
        // Code to retrieve all messages from the database
        return new java.util.ArrayList<>();
    }
}