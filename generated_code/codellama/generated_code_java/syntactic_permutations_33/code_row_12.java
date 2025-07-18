package com.example;
    import java.net.URL;
    import javax.servlet.http.HttpServletRequest;
    public class Redirector {
        public void redirect_invalid_url(HttpServletRequest request){
            URL url = new URL(request.getParameter("url"));
            if (url.getHost().equals("example.com")){
                response.sendRedirect(url);
            }else{
                response.getWriter().write("Invalid URL");
            }
        }
    }