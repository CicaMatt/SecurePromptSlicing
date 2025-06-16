The following code was generated automatically:

package com;
import java.io.*; 
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet{
    public void doPost(HttpServletRequest request,HttpServletResponse response)throws IOException,ServletException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (LoginService.checkUser(username,password)) {
            RequestDispatcher rd=request.getRequestDispatcher("welcome.html");
            rd.forward(request,response);
        } else{
            RequestDispatcher rd=request.getRequestDispatcher("login.html");
            PrintWriter out = response.getWriter();
            out.println("<font color=red>username or password is wrong.</font>");
            rd.include(request,response);
        }
    }
}
class LoginService {
    public static boolean checkUser(String username, String password){
        //check if the user exists in the database
        return true;
    }
}