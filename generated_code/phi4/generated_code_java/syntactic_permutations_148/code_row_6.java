import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insert_user_message_in_db(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Assuming 'mainPage.jsp' is the main page
        } else {
            response.getWriter().println("Failed to post message.");
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        // Here we should have database insertion logic.
        // This is a placeholder for demonstration purposes.
        System.out.println("Inserting into DB: User = " + username + ", Message = " + message);
        return true;  // Simulate successful insertion
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/displayMessages")
public class DisplayMessagesServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Logic to retrieve messages from the database would go here.
        String[] messages = getMessagesFromDatabase();

        request.setAttribute("messages", messages);
        request.getRequestDispatcher("/display.jsp").forward(request, response); // Assuming 'display.jsp' shows messages
    }

    private String[] getMessagesFromDatabase() {
        // Placeholder for getting messages from a database
        return new String[]{
            "User1: Hello World!",
            "User2: Hi there!"
        };
    }
}
