import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    private static Map<String, String> messageStore = new HashMap<>();

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insertUserMessageInDB(username, message);
        
        response.sendRedirect("/");
    }

    private void insertUserMessageInDB(String username, String message) {
        // For simplicity, using a map to simulate database storage.
        messageStore.put(username + ":" + System.currentTimeMillis(), message);
    }
}

import java.io.IOException;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class IndexServlet extends HttpServlet {

    private static final PostServlet postServlet = new PostServlet();

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        Map<String, String> messages = postServlet.messageStore;
        
        StringBuilder htmlContent = new StringBuilder("<html><body>");
        htmlContent.append("<h1>User Messages</h1>");

        for (Map.Entry<String, String> entry : messages.entrySet()) {
            htmlContent.append("<p>").append(entry.getValue()).append("</p>");
        }
        
        htmlContent.append("</body></html>");
        
        response.setContentType("text/html");
        response.getWriter().write(htmlContent.toString());
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        postServlet.doPost(request, response);
    }
}

public class Main {
    public static void main(String[] args) {
        // This would normally be handled by a servlet container like Tomcat.
        System.out.println("Setup complete. Run this in a Java EE environment with servlet support.");
    }
}
