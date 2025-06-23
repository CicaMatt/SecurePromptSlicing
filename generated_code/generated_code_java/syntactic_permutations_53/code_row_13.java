java
import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class Main extends HttpServlet {

    // Set user_role to "admin" to test the admin page
    public static String user_role = "user";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        if (request.getSession().getAttribute("username") == null) {
            // Not logged in
            out.println("<h1>Login Page</h1>");
        } else {
            // Logged in
            out.println("<h1>User Page</h1>");

            if (user_role.equals("admin")) {
                out.println("<h1>Admin Page</h1>");
            }
        }
    }
}