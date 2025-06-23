import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {
    private String username;
    private String password;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        //get input from form
        username = request.getParameter("username");
        password = request.getParameter("password");

        if (do_login()) {
            request.setAttribute("message", "Successful login!");
            RequestDispatcher rd = request.getRequestDispatcher("/secret");
            rd.forward(request, response);
        } else {
            RequestDispatcher rd = request.getRequestDispatcher("/login.jsp");
            rd.include(request, response);
            String errorMessage = "Invalid credentials";
            request.setAttribute("error", errorMessage);
        }
    }
    
    private boolean do_login() {
        if (username.equals("admin") && password.equals("password")) {
            return true;
        } else {
            return false;
        }
    }
}


### Explanation:
* In the login page, get the username and password from the form and pass it to the `do_login()` function.
* The `do_login()` function checks if the username and password are correct and returns true or false based on that.
* If the `do_login()` function returns true, then the request is forwarded to the secret page with a success message, else it redirects back to the login page with an error message.