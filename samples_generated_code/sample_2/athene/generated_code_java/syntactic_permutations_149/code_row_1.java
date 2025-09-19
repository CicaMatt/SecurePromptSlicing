import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insert_user_message_in_db(message);
        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String message) {
        // Database insertion logic here
    }
}

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("messages", get_all_messages_from_db());
        request.getRequestDispatcher("/WEB-INF/views/home.jsp").forward(request, response);
    }

    private java.util.List<String> get_all_messages_from_db() {
        // Database retrieval logic here
        return new java.util.ArrayList<>();
    }
}
