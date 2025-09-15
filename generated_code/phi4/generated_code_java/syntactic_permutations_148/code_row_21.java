import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insertUserMessageInDb(username, message);
        }

        response.sendRedirect("mainPage.jsp");
    }
    
    private void insertUserMessageInDb(String username, String message) {
        // Simulate database insertion
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        
        // Actual database code would go here.
    }
}

import java.io.IOException;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/displayMessages")
public class DisplayMessagesServlet extends HttpServlet {

    private static final ArrayList<String> messages = new ArrayList<>();

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Simulate fetching from a database
        request.setAttribute("messages", messages);
        
        request.getRequestDispatcher("messages.jsp").forward(request, response);
    }

    public static void addMessage(String message) {
        messages.add(message);
    }
}
