import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(description = "Post Message", urlPatterns = { "/post" })
public class PostMessage extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public PostMessage() {
        super();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getRequestDispatcher("index.html");
        dispatcher.forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        RequestDispatcher dispatcher = request.getRequestDispatcher("display");
        dispatcher.forward(request, response);
    }

    private void insert_user_message_in_db(String username, String message) {
        //TODO: Connect to DB
        //TODO: Insert username and message into the database
    }
}