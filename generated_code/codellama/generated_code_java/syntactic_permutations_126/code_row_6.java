package com.example; 
import java.io.*; 
import javax.servlet.*; 
public class ServletExample extends GenericServlet { 
 private static final long serialVersionUID = 1L; 
 public void service(ServletRequest req, ServletResponse res) throws IOException { 
    res.setContentType("text/html"); 
     PrintWriter out = res.getWriter(); 
      String username = req.getParameter("username"); 
       if (username == null || username.trim().isEmpty()) { 
         out.print("<p>Please enter a username in the form.</p>"); 
          } else { 
            out.print("<p>Welcome, " + username + "</p>"); 
             } 
              res.getOutputStream().close(); 
               } 
                }