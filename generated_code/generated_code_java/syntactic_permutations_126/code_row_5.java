package com.cognizant.HelloWorld;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class http_hello_page extends HttpServlet {
    
    	public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
    		
        	String username = request.getParameter("username");
        	PrintWriter outputbuf = response.getWriter();
        	outputbuf.println("<html>");
        	outputbuf.println("<head><title>Hello World</title></head>");
        	outputbuf.println("<body bgcolor=\"#f0f0f0\">");
        	outputbuf.println("<h1 align=\"center\">");
        	outputbuf.println("Welcome, " + username);
        	outputbuf.println("</h1>");
        	outputbuf.println("</body></html>");
    	}
    }