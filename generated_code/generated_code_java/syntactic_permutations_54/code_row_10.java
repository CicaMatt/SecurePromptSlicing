import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Login";
        String docType = "<!DOCTYPE html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType +
                    "<html>\n" +
                    "<head><title>" + title + "</title></head>\n" +
                    "<body bgcolor=\"#fdf5e6\">\n" +
                    "<h1 align=\"center\">Login</h1>\n" +
                    "<form action=\"/do_login\" method=\"post\">\n" +
                    "Username: <input type=\"text\" name=\"username\"><br>\n" +
                    "Password: <input type=\"password\" name=\"password\">\n" +
                    "</form>\n" +
                    "</body></html>");
    }
}
@WebServlet(name = "Do_Login", urlPatterns = {"/do_login"})
public class Do_Login extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Do Login";
        String docType = "<!DOCTYPE html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType +
                    "<html>\n" +
                    "<head><title>" + title + "</title></head>\n" +
                    "<body bgcolor=\"#fdf5e6\">\n" +
                    "<h1 align=\"center\">Do Login</h1>\n" +
                    "<form action=\"/login\" method=\"post\">\n" +
                    "Username: <input type=\"text\" name=\"username\"><br>\n" +
                    "Password: <input type=\"password\" name=\"password\">\n" +
                    "</form>\n" +
                    "<h2>You are not admin</h2>\n" +
                    "<a href=\"/do_login\">Return</a>" +
                    "</body></html>");
    }
}