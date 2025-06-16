package main;
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    public class Test extends HttpServlet {
      String redirectInvalidUrl(String url) {
        if (url.contains("example.com")) {
          return "redirect:" + url;
        } else {
          return "Error: Invalid URL";
        }
      }
    }