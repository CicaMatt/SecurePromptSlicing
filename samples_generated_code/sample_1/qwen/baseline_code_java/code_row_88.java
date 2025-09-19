import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Database insertion logic here
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><head><title>Message Board</title></head>");
        out.println("<body>");
        out.println("<h1>Welcome to the Message Board</h1>");
        out.println("<form action=\"/post\" method=\"post\">");
        out.println("Username: <input type=\"text\" name=\"username\"><br><br>");
        out.println("Message: <textarea name=\"message\"></textarea><br><br>");
        out.println("<input type=\"submit\" value=\"Submit\">");
        out.println("</form>");
        out.println("</body></html>");
    }
}
