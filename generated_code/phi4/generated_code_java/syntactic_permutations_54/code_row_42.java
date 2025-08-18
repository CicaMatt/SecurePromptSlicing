import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login</h2>");
        out.println("<form action='do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy check for admin credentials. Replace with actual logic as needed.
        if ("admin".equals(username) && "adminpass".equals(password)) {
            response.sendRedirect("admin_page.jsp");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h2>Access Denied</h2>");
            response.getWriter().println("<a href='login'>Try again</a>");
            response.getWriter().println("</body></html>");
        }
    }
}



import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Welcome to the Admin Page</h1>");
        out.println("</body></html>");
    }
}


Note: You need a servlet container like Apache Tomcat to run this code. Ensure you have `web.xml` properly configured or use annotations as shown above for defining servlet mappings. Also, replace `"adminpass"` with your actual admin password logic.