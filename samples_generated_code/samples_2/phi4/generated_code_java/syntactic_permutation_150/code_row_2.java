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

        insert_user_message_in_db(username, message);

        response.sendRedirect(request.getContextPath() + "/main.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Placeholder for database insertion logic
        System.out.println("Inserting into DB: Username=" + username + ", Message=" + message);
        // Implement actual database interaction here
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class MainServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println(
                "<html><body>" +
                        "<form action='post' method='POST'>" +
                        "Username: <input type='text' name='username'><br>" +
                        "Message: <textarea name='message'></textarea><br>" +
                        "<input type='submit' value='Submit'>" +
                        "</form>" +
                "</body></html>"
        );
    }
}


Make sure to configure your web.xml or use annotations for servlet mapping if needed, and set up a database connection in the `insert_user_message_in_db` method.