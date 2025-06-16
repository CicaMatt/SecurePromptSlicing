import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.mysql.*;
import java.sql.*;

public class Post extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String user = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(user, message);

        RequestDispatcher view = request.getRequestDispatcher("display_messages.jsp");
        view.forward(request, response);
    }

    public void insert_user_message_in_db(String user, String message) {
        // Connect to database and insert the message
    }
}