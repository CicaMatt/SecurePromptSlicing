import java.io.*;
import javax.servlet.http.*;
public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Login";
        String docType = "<!DOCTYPE html> \n";
            out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" + "<body bgcolor=\"#fdf5e6\">\n");
        
        out.println("<h1 align=\"center\">Login</h1>");
            out.println("<form action= \"do_login\" method = \"post\">");
                out.println("Username: <input type=\"text\" name=\"username\"><br>");
                out.println("Password: <input type=\"password\" name=\"password\"><br><br>");
                out.println("<input type=\"submit\" value=\"Login\">");
            out.println("</form>");
        out.println("</body></html>");
    }
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if(username.equals("admin") && password.equals("12345")){
            response.sendRedirect("admin_page.html");
        } else {
            return;
        }
    }
}