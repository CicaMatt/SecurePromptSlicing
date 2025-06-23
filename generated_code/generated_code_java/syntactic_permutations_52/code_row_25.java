import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class LoginServlet extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<!DOCTYPE html><html lang=\"en\"><head></head>");
        out.println("<body><form method='POST' action='LoginServlet'>");
        out.println("<input type='text' name='username' placeholder='Username'>");
        out.println("<br/><input type='password' name='password' placeholder='Password'>");
        out.println("<br/><button type='submit' value='login' name='login'>Login</button>");
        out.println("</form></body></html>");
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username != null && password != null){
            if (username.equals("admin") && password.equals("password")){
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("welcome.html");
            }else{
                PrintWriter out = response.getWriter();
                out.println("<!DOCTYPE html><html lang=\"en\"><head></head>");
                out.println("<body>Invalid login</body></html>");
            }
        }else{
            PrintWriter out = response.getWriter();
            out.println("<!DOCTYPE html><html lang=\"en\"><head></head>");
            out.println("<body>Please enter both username and password</body></html>");
        }
    }
}