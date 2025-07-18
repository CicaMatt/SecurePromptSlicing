import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.util.*;
    
    public class info extends HttpServlet{
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            PrintWriter out = response.getWriter();
            String username = (String)request.getSession().getAttribute("username");
            String email = (String)request.getSession().getAttribute("email");
            String ssn = (String)request.getSession().getAttribute("ssn");
    	    out.println(username + ":" + email + ":" + ssn);
        }
    }
