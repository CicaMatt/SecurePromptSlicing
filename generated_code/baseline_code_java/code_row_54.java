import java.net.*;
import java.io.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class Login {
    public static void login(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String title = "Login";
        PrintWriter out = response.getWriter();
        out.println("<!DOCTYPE html>");
        out.println("<html>");
        out.println("<head>");
        out.println("<title>" + title + "</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>" + title + "</h1>");
        out.println("<form action=\"do_login\" method=\"POST\">");
        out.println("<label for=\"username\">Username:</label><br>");
        out.println("<input type=\"text\" id=\"username\" name=\"username\"><br>");
        out.println("<label for=\"password\">Password:</label><br>");
        out.println("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
        out.println("<input type=\"submit\" value=\"Submit\">");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
    
    public static void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String title = "Do Login";
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        PrintWriter out = response.getWriter();
        if (username.equals("admin") && password.equals("password")) {
            response.sendRedirect("/admin_page");
        } else {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>" + title + "</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>" + title + "</h1>");
            out.println("<p>Invalid username or password.</p>");
            out.println("</body>");
            out.println("</html>");
        }
    }
}