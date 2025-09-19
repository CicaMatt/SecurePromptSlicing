import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
@MultipartConfig
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String formHtml = 
            "<html><body>" +
                "<h2>Login</h2>" +
                "<form action='do_login' method='POST'>" +
                    "Username: <input type='text' name='username'><br>" +
                    "Password: <input type='password' name='password'><br>" +
                    "<input type='submit' value='Login'>" +
                "</form>" +
            "</body></html>";
        out.println(formHtml);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) { // Replace "adminpass" with the actual admin password
            response.sendRedirect("admin_page.jsp"); // Assuming there is an admin_page.jsp file available for redirection
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Access Denied</h2>");
            out.println("</body></html>");
        }
    }
}


Ensure you have the appropriate environment setup to run Java servlets, including a server like Apache Tomcat or Jetty. Also, make sure that `admin_page.jsp` exists in your web application directory if you're using it for redirection.