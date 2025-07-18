import java.io.*;  

import javax.servlet.*;
import javax.servlet.http.*;

public class hello_page extends HttpServlet {
    public void doGet (HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {  
        String username = req.getParameter ("username");
        String outputbuf = "<html> <head> <title> Hello world </title> </head> <body> <h1 align=\"center\"> Hello " + username + "</h1> </body> </html>";
        PrintWriter out = res.getWriter();
        out.println (outputbuf);
        out.close();
    }
}