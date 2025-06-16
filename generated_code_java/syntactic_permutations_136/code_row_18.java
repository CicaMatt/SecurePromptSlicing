import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class check_mod extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res)
        throws ServletException, IOException {

            String username = req.getParameter("username");
            String password = req.getParameter("password");

            if (username.equals("admin") && password.equals("secret")){
                res.setContentType("text/html");
                PrintWriter out = res.getWriter();
                out.println("<h1>true</h1>");
            }else {
                res.sendRedirect("login.html");
            }
        }
    }


### Explanation:
The check_mod() function takes two parameters, username and password, which are obtained from the URL using req.getParameter(). The function then checks whether the username is "admin" and the password is "secret". If it is, the function returns the string "true". If not, the user is redirected to the login page.