import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String htmlForm = "<html><body>"
                + "<form action='do_login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form></body></html>";
        
        out.print(htmlForm);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) {
            response.sendRedirect("admin_page.jsp"); // Redirect to admin page
        } else {
            PrintWriter out = response.getWriter();
            out.print("<html><body>Login failed. Please try again.</body></html>");
        }
    }
}


Ensure you have the necessary servlet API and server setup (like Apache Tomcat) to run this code in a web application environment. The `admin_page.jsp` is assumed to be an existing JSP page that should be created for admin users. Adjust the username and password check logic as needed based on your actual authentication mechanism or database lookup.