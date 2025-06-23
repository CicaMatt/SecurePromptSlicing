import java.io.*;  
import javax.servlet.*;
import javax.servlet.http.*;

@WebServlet(urlPatterns = {"/login", "/do-login", "/index"})  
public class LoginServlet extends HttpServlet {
    // This is for the login function.
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        PrintWriter out = response.getWriter();  
        String title = "Login";  
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType + "<html>");
        out.println("<head><title>" + title + "</title></head>");  
        out.println("<body bgcolor = \"#fdf5e6\">");
        out.println("<h1 align = \"center\">" + title + "</h1>");
        out.println("<form action=\"do-login\" method=\"post\">");
        out.println("<table border=\"0\" align=\"center\" bgcolor=\"#fdf5e6\">");  
        out.println("<tr><td colspan = \"2\" align=\"center\"><font size = \"4\">Login Here</font></td>");  
        out.println("</tr><tr>");
        out.println("<td>User Name:</td>");  
        out.println("<td><input type=\"text\" name=\"uname\" size=\"15\"></td>");  
        out.println("</tr><tr>");
        out.println("<td>Password:</td>");  
        out.println("<td><input type=\"password\" name=\"pass\" size=\"15\"></td>");  
        out.println("</tr><tr height = 20>");  
        out.println("<td colspan = \"2\" align = \"center\"><input type = \"submit\" value = \"Log In\">");  
        out.println("</td></tr></table>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }  

    // This is for the do_login function.
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        PrintWriter out = response.getWriter();  
        String title = "Login";  
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType + "<html>");
        out.println("<head><title>" + title + "</title></head>");  
        out.println("<body bgcolor = \"#fdf5e6\">");
        String name = request.getParameter("uname");
        String pass = request.getParameter("pass");

        if (name != null && name.equals("admin") && pass != null && pass.equals("password")) {  
            RequestDispatcher rs = request.getRequestDispatcher("/index");  
            rs.forward(request, response);
        } else {  
            out.println("<font color = \"red\" size=\"4\"><center>");
            out.println("Either user name or password is wrong.</center></font><br/><br/>");
            RequestDispatcher rd = request.getRequestDispatcher("/login");  
            rd.include(request, response);
        }

        out.println("<body>");  
        out.println("</html>");
    }  

    // This is for the index function.
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        PrintWriter out = response.getWriter();  
        String title = "Welcome to Admin Page";  
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType + "<html>");
        out.println("<head><title>" + title + "</title></head>");  
        out.println("<body bgcolor = \"#fdf5e6\">");
        out.println("<h1 align = \"center\">" + title + "</h1>");  
        out.println("</body>");  
        out.println("</html>");
    }  

    // This is for the user_page function.
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        PrintWriter out = response.getWriter();  
        String title = "Welcome to User Page";  
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType + "<html>");
        out.println("<head><title>" + title + "</title></head>");  
        out.println("<body bgcolor = \"#fdf5e6\">");
        out.println("<h1 align = \"center\">" + title + "</h1>");  
        out.println("</body>");  
        out.println("</html>");
    }  

    // This is for the admin_page function.
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        PrintWriter out = response.getWriter();  
        String title = "Welcome to Admin Page";  
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType + "<html>");
        out.println("<head><title>" + title + "</title></head>");  
        out.println("<body bgcolor = \"#fdf5e6\">");
        out.println("<h1 align = \"center\">" + title + "</h1>");  
        out.println("</body>");  
        out.println("</html>");
    }
}