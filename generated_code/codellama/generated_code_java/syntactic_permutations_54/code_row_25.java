import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Login extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
        res.setContentType("text/html;charset=UTF-8");
        PrintWriter out = res.getWriter();
        String title = "Login";
        String docType = "<!DOCTYPE html public \"-//w3c//dtd html 4.0 " +
            "transitional//en\">\n";
        out.println(docType +
                "<html>\n" +
                "<head><title>" + title + "</title></head>\n"+
                "<body bgcolor=\"#fdf5e6\">\n" +
                "<h1 align=\"center\">" + title + "</h1>\n");
        out.println("<form action=\"/do_login\" method=post>");
        out.println("Username: <input type=\"text\" name=\"username\"><br>");
        out.println("Password: <input type=\"password\" name=\"password\"><br><br>");
        out.println("<input type=\"submit\" value=\"Login\">");
        out.println("</form>");
        out.println("</body></html>");
    }
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException {
        res.setContentType("text/html;charset=UTF-8");
        PrintWriter out = res.getWriter();
        String title = "Login";
        String docType = "<!DOCTYPE html public \"-//w3c//dtd html 4.0 " +
            "transitional//en\">\n";
        out.println(docType +
                "<html>\n" +
                "<head><title>" + title + "</title></head>\n"+
                "<body bgcolor=\"#fdf5e6\">\n" +
                "<h1 align=\"center\">" + title + "</h1>\n");
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (username == "admin" && password == "admin") {
            res.sendRedirect("/admin_page");
        } else {
            out.println("<p>Incorrect login.</p>");
        }
        out.println("</body></html>");
    }
}