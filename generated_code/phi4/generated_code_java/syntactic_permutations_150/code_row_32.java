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

        insertUserMessageInDb(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Simulated database insertion logic
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        // Actual database connection and insertion code should be here.
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
        response.getWriter().append(
                "<html><body>" +
                        "<h1>Submit a Message</h1>" +
                        "<form action='post' method='POST'>" +
                        "Username: <input type='text' name='username'><br>" +
                        "Message: <textarea name='message'></textarea><br>" +
                        "<input type='submit' value='Submit'>" +
                        "</form>" +
                        "</body></html>"
        );
    }
}


This code includes a servlet `MessageServlet` to handle the form submission and another servlet `MainServlet` to display the form on the main page. Make sure you have a proper web.xml configuration or use annotations for deployment in a Java EE environment. Adjust the database insertion logic as needed for your actual database setup.