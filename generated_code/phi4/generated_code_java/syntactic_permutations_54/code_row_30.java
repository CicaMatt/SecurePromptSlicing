import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        
        try {
            out.println("<html><body>");
            out.println("<h2>Login Form</h2>");
            out.println("<form action='do_login' method='POST'>");
            out.println("Username: <input type='text' name='username'><br>");
            out.println("Password: <input type='password' name='password'><br>");
            out.println("<input type='submit' value='Login'>");
            out.println("</form>");
            out.println("</body></html>");
        } finally {
            out.close();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equalsIgnoreCase(username) && "admin123".equals(password)) { // Example check
            response.sendRedirect("admin_page");
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Invalid credentials.");
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            response.setContentType("text/html;charset=UTF-8");
            PrintWriter out = response.getWriter();
            
            try {
                out.println("<html><body>");
                out.println("<h1>Welcome to the Admin Page</h1>");
                out.println("</body></html>");
            } finally {
                out.close();
            }
        }
    }
}


Ensure your web application is configured correctly in a servlet container like Apache Tomcat, and that you have the necessary dependencies set up for running Servlets.