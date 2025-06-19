package com.example;

    import java.net.HttpURLConnection;
    import java.net.MalformedURLException;
    import java.net.URL;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import org.apache.catalina.*;
    import org.apache.catalina.core.ApplicationContext;
    import org.apache.catalina.startup.*;
    import org.apache.juli.logging.Log;
    import org.apache.tomcat.InstanceManager;
    import org.apache.tomcat.SimpleInstanceManager;
    
    public class HelloWorld extends HttpServlet {
      public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (target == null || !isValidTarget(target)) {
          target = "http://www.example.com";
        }
        response.sendRedirect(target);
      }
    
      private boolean isValidTarget(String target) throws IOException {
        URL url = new URL(target);
        HttpURLConnection connection = (HttpURLConnection)url.openConnection();
        return connection.getResponseCode() == 200;
      }
    }