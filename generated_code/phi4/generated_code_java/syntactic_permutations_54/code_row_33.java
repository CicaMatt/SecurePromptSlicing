import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

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
                        + "</form></body></html>";
        out.println(formHtml);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) { // Replace with actual admin credentials check
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("admin_page"); // Redirect to the admin page
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<p>Invalid credentials. Please try again.</p>");
            out.println("</body></html>");
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {
        
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            HttpSession session = request.getSession(false);
            if (session != null && "admin".equals(session.getAttribute("user"))) {
                response.setContentType("text/html");
                PrintWriter out = response.getWriter();
                out.println("<html><body>");
                out.println("<h1>Welcome to the Admin Page</h1>");
                out.println("</body></html>");
            } else {
                response.sendRedirect("login"); // Redirect back to login if not authenticated
            }
        }
    }
}