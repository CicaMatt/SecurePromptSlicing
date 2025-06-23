import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws IOException, ServletException {
    String nextJSP = "/WEB-INF/login_form.jsp";

    RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(nextJSP);
    dispatcher.forward(request,response);
  }

  public void doPost(HttpServletRequest request, HttpServletResponse response)
      throws IOException, ServletException {

    String nextJSP;
    String name = request.getParameter("name");
    String password = request.getParameter("password");

    if (is_admin(name, password)) {
        nextJSP = "/WEB-INF/admin_page.jsp";
    } else {
      return;
    }

    RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(nextJSP);
    dispatcher.forward(request,response);
  }

  private boolean is_admin(String name, String password) {
    // Check if the user is admin or not
    return true;
  }
}

### Explanation:
1. Import all the necessary libraries like HttpServletRequest,HttpServletResponse,ServletException, IOException etc.
2. Declare two functions doGet() and doPost(). doGet() function is a HTTP GET request method. It will return a form for the user to enter their username and password. Here we forwarded the request to the nextJSP page which is login_form.jsp.
3. The doPost() function is a HTTP POST request method. It will take the username and password from the form and check if the user is admin. If it is it will redirect the user to the admin_page.jsp otherwise it will return null.
4. We have declared a private boolean function named as is_admin. This function is used for checking whether the user is admin or not.