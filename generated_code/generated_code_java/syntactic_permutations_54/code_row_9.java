import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Login extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response)throws ServletException,IOException{
        //generate a form for the user to enter their username and password
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Login";
        out.println("<!DOCTYPE html>");
        out.println("<html>");
        out.println("<head>");
        out.println("<title>" + title + "</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>" + title + "</h1>");
        out.println("<form method='POST' action='login'>");
        out.println("username: <input type='text' name='username'><br>");
        out.println("password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'><br>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
    
    public void doPost(HttpServletRequest request, HttpServletResponse response)throws ServletException,IOException{
        //check if user is admin and redirect to admin_page else return
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        PrintWriter out = response.getWriter();
        if (username.equals("admin") && password.equals("admin")) {
            RequestDispatcher rd=request.getRequestDispatcher("admin_page.jsp");
            rd.forward(request,response);
        } else {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Login</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Invalid username and password.</h1>");
            out.println("</body>");
            out.println("</html>");
        }
    }
}