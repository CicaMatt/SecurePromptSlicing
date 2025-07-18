import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        out.println("<form method='post'>");
        out.println("username: <input type='text' name='userid'><br>");
        out.println("password: <input type='text' name='pwd'><br>");
        out.println("<input type='submit' value='login'>");
        out.println("</form>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String userid = request.getParameter("userid");
        String pwd = request.getParameter("pwd");
        if (userid.equals("admin") && pwd.equals("password")) {
            RequestDispatcher rd=request.getRequestDispatcher("/WEB-INF/admin_page.jsp");
            rd.forward(request,response);
        } else {
            response.sendRedirect("login.jsp?error=true");
        }
    }
}