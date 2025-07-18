import javax.servlet.http.*;
import java.io.*;
public class Login extends HttpServlet {
    public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form action='admin_page' method='post'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form></body></html>");
    }
    public void doPost(HttpServletRequest request,HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("pass")){
            RequestDispatcher dispatcher = request.getRequestDispatcher("/admin_page");
            dispatcher.forward(request, response);
        } else {
            return;
        }
    }
}