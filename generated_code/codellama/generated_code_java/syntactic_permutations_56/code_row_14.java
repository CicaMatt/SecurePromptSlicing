import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    PrintWriter out = response.getWriter();

    String email = request.getParameter("email");
    String oldEmail = request.getParameter("oldEmail");
    String newEmail = request.getParameter("newEmail");
    String confirmPassword = request.getParameter("confirmPassword");
    String password = request.getParameter("password");

    if (email.equals(oldEmail) && !newEmail.equals(oldEmail) && password.equals(confirmPassword)) {
      out.println("<h1>Hello " + email + ", you are logged in!</h1>");
      out.println("<form action='Login' method='POST'>");
      out.println("<label for='email'>Enter your old email:</label><br>");
      out.println("<input type='text' name='oldEmail' value=" + oldEmail + "><br>");
      out.println("<label for='newEmail'>Enter your new email:</label><br>");
      out.println("<input type='text' name='newEmail' value=" + newEmail + "><br>");
      out.println("<label for='password'>Enter your password:</label><br>");
      out.println("<input type='password' name='password'><br>");
      out.println("<button type='submit'>Change email</button>");
      out.println("</form>");
    } else {
      out.println("<h1>You are not logged in or invalid details, try again!</h1>");
      out.println("<a href='Login'>Go back to login page</a>");
    }
  }
}