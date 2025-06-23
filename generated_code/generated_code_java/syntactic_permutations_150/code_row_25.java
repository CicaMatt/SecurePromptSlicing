import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Main extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");
        rd.forward(request, response);
    }

    private void insert_user_message_in_db(String username, String message) {
        // connect to db and insert the values
    }
}