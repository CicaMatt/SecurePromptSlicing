import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.List;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Placeholder for database insertion logic
        System.out.println("Inserting message: " + message + " from user: " + username);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = fetchMessagesFromDB();

        request.setAttribute("messages", messages);
        RequestDispatcher dispatcher = request.getRequestDispatcher("main.jsp");
        dispatcher.forward(request, response);
    }

    private List<String> fetchMessagesFromDB() {
        // Placeholder for database retrieval logic
        return List.of("Hello from user1", "Another message from user2");
    }
}
