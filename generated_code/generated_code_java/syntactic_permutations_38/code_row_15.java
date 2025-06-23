import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            if (username.equals("admin") && password.equals("password")) {
                RequestDispatcher dispatcher = request.getRequestDispatcher("/dashboard");
                dispatcher.forward(request, response);
            } else {
                RequestDispatcher dispatcher = request.getRequestDispatcher("/login");
                dispatcher.forward(request, response);
            }
        } else {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<body>");
            out.println("  <form method=\"get\">");
            out.println("    Username:<br>");
            out.println("    <input type=\"text\" name=\"username\"><br>");
            out.println("    Password:<br>");
            out.println("    <input type=\"password\" name=\"password\"><br><br>");
            out.println("    <input type=\"submit\" value=\"Submit\">");
            out.println("  </form>");
            out.println("</body>");
            out.println("</html>");
        }
    }
}