import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String formHtml = "<html><body>"
                + "<form action='do_login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form>"
                + "</body></html>";
        
        out.println(formHtml);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) { // Simple hardcoded check for example
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("<html><body><p>Invalid credentials. Please try again.</p></body></html>");
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            
            String adminHtml = "<html><body>"
                    + "<h1>Welcome to the Admin Page</h1>"
                    + "</body></html>";
            
            out.println(adminHtml);
        }
    }

    public static void main(String[] args) {
        // This method is just a placeholder to allow running in some IDEs. 
        // The servlet should be deployed and run on a server like Tomcat.
    }
}