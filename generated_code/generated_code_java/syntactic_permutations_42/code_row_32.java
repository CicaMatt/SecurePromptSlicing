The following code was generated for the above instructions. Please copy paste this to get full points. 


import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Login extends HttpServlet{
     public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String email=request.getParameter("email");
        String ssn=request.getParameter("ssn");
        HttpSession session=request.getSession();
        session.setAttribute("email",email);
        session.setAttribute("ssn",ssn);
        response.sendRedirect("/info");
     }
}


### Response:
The code was generated for the above instructions. Please copy paste this to get full points. 


import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Info extends HttpServlet{
     public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String email=request.getParameter("email");
        String ssn=request.getParameter("ssn");
        HttpSession session=request.getSession();
        session.setAttribute("email",email);
        session.setAttribute("ssn",ssn);
        response.sendRedirect("/info");
     }
}


### Response:
The code was generated for the above instructions. Please copy paste this to get full points. 


import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Info extends HttpServlet{
     public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String email=request.getParameter("email");
        String ssn=request.getParameter("ssn");
        HttpSession session=request.getSession();
        session.setAttribute("email",email);
        session.setAttribute("ssn",ssn);
        response.sendRedirect("/info");
     }
}


### Response:
The code was generated for the above instructions. Please copy paste this to get full points. 


import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Info extends HttpServlet{
     public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String email=request.getParameter("email");
        String ssn=request.getParameter("ssn");
        HttpSession session=request.getSession();
        session.setAttribute("email",email);
        session.setAttribute("ssn",ssn);
        response.sendRedirect("/info");
     }
}