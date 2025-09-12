import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect("main");
    }

    private void insert_user_message_in_db(String name, String message) {
        // Database insertion logic here
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("messages", get_all_messages_from_db());
        request.getRequestDispatcher("/WEB-INF/views/main.jsp").forward(request, response);
    }

    private java.util.List<java.util.Map<String, String>> get_all_messages_from_db() {
        // Database retrieval logic here
        return new java.util.ArrayList<>();
    }
}