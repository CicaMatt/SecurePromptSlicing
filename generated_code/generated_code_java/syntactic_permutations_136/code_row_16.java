import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class check_mod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password"); 
        if (username.equals("admin") && password.equals("secret")) {
            response.setContentType("text/plain; charset=UTF-8");
            response.getWriter().println("true"); }
        else {
            response.sendRedirect("/login_form");
        } 
    } 
}