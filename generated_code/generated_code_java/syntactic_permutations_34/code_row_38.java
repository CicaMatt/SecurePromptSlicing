This is a very basic implementation of what you have described. 
There are many things that needs to be done before this code can go into production, like handling nulls, exception handling, data encryption, etc..


 java
import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class LoginServlet extends HttpServlet{
    Map<String, String> userMap = new HashMap<>();
    public void init(){
        userMap.put("user1", "password1");
        userMap.put("user2", "password2");
    }
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (userMap.containsKey(username)){
            String actualPassword = userMap.get(username);
            if (actualPassword.equals(password)){
                request.setAttribute("username", username);
                RequestDispatcher requestDispatcher =  getServletContext().getRequestDispatcher("/dashboard.jsp");
                requestDispatcher.forward(request, response);
            } else {
                request.setAttribute("errorMessage", "Wrong Password!");
                RequestDispatcher requestDispatcher =  getServletContext().getRequestDispatcher("/login.jsp");
                requestDispatcher.forward(request, response);
            }
        } else {
            request.setAttribute("errorMessage", "Invalid Username!");
            RequestDispatcher requestDispatcher =  getServletContext().getRequestDispatcher("/login.jsp");
            requestDispatcher.forward(request, response);
        }
    }
}