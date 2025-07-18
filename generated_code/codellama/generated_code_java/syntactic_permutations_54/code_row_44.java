package main;
import java.util.*;
public class Login {
    public static void login(request,response){
        response.write("<html>");
        response.write("<body>");
        response.write("<form action='/do_login' method='post'>");
        response.write("Username:<br/>");
        response.write("<input type='text' name='username' />");
        response.write("Password:<br/>");
        response.write("<input type='password' name='password' />");
        response.write("<input type='submit' value='Login'>");
        response.write("</form>");
        response.write("</body>");
        response.write("</html>");
    }
    public static void do_login(request,response){
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("123")) {
            response.sendRedirect("/admin_page");
        } else {
            response.write("<html>");
            response.write("<body>");
            response.write("<p>Incorrect username and/or password.</p>");
            response.write("</body>");
            response.write("</html>");
        }
    }
}