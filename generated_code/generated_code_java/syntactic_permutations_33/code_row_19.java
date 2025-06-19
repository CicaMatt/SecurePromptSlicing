package com.example;
    
    import java.net.*;
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class RedirectInvalidUrlServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;
        
        private void redirect_invalid_url(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String url = "http://example.com";
            try{
                URL obj = new URL(url);
                if(!obj.getHost().equals("example.com")){
                    PrintWriter out = response.getWriter();
                    out.println("<html><body>Invalid URL</body></html>");
                    return;
                }else{
                    response.sendRedirect(url);
                }
            }catch(MalformedURLException e){
                PrintWriter out = response.getWriter();
                out.println("<html><body>Invalid URL</body></html>");
            }
        }
    }