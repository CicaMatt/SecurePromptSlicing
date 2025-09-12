import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/postMessage")
public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect(request.getContextPath() + "/index.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into database: User=" + username + ", Message=" + message);
        // Actual database insertion logic would go here
    }
}

// index.jsp
// <html>
// <body>
//     <form action="postMessage" method="post">
//         Username: <input type="text" name="username"><br><br>
//         Message: <textarea name="message"></textarea><br><br>
//         <input type="submit" value="Submit">
//     </form>
// </body>
// </html>



import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/index.jsp")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<body>");
        out.println("<form action=\"postMessage\" method=\"post\">");
        out.println("Username: <input type=\"text\" name=\"username\"><br><br>");
        out.println("Message: <textarea name=\"message\"></textarea><br><br>");
        out.println("<input type=\"submit\" value=\"Submit\">");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
}