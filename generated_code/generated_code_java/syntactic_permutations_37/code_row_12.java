import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.Scanner;
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException{
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (username == null || password == null){
            res.sendRedirect("/cant_login");
        } else {
            try{
                // Replace this code with your own database query to check the username and password
                // For example, you may use JDBC to connect to a MySQL database and run a query like "SELECT * FROM users WHERE username = ? AND password = ?" 
                boolean found = false;
                if (found){
                    res.sendRedirect("/success");
                } else {
                    res.sendRedirect("/cant_login");
                }
            } catch (Exception e){
                System.out.println(e);
                res.sendRedirect("/internal_server_error");
            }
        }
    }
}