import java.io.*;  
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {  
    public void doGet(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {   
        PrintWriter out = response.getWriter();  
        String username = request.getParameter("username");  
        String password = request.getParameter("password");  
          if(username != null && password != null){  
            if(username.equals("admin") && password.equals("admin")){  
              HttpSession session = request.getSession();  
              session.setAttribute("username", username);  
              response.sendRedirect("/secret.jsp");  
            }else{  
              out.println("Invalid login credentials.");  
            }  
          }
        out.println("<html>");  
        out.println("<head><title>Login Page</title></head>");
        out.println("<body>");  
        out.println("<h1>Login Here</h1>");  
        out.println("<form action='login' method='get'>");  
        out.println("Username: <input type='text' name='username' size=25><br />");  
        out.println("Password: <input type='password' name='password' size=25><br />");  
        out.println("<input type='submit' value='Login'>");  
        out.println("</form>");  
        out.println("</body></html>");  
    }  
}  


import java.io.*;  
import javax.servlet.http.*;

public class SecretPageServlet extends HttpServlet {  
    public void doGet(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {   
        PrintWriter out = response.getWriter();  
          if(request.getSession().getAttribute("username") != null){  
            out.println("<html>");  
            out.println("<head><title>Secret Page</title></head>");
            out.println("<body>");  
            out.println("<h1>Welcome to secret page.</h1>");  
            out.println("</body></html>");  
          }else{  
            response.sendRedirect("/login");  
          }
    }  
}  


import java.io.*;  
import javax.servlet.http.*;

public class IndexServlet extends HttpServlet {  
    public void doGet(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {   
        PrintWriter out = response.getWriter();  
          if(request.getSession().getAttribute("username") != null){  
              response.sendRedirect("/secret");  
          }else{  
            out.println("<html>");  
            out.println("<head><title>Index Page</title></head>");
            out.println("<body>");  
            out.println("<h1>Welcome to index page.</h1>");  
            out.println("<a href='login'>Login here</a>");  
            out.println("</body></html>");  
          }
    }  
}