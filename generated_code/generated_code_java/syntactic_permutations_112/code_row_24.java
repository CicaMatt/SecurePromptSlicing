import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.net.*;

public class PingDecorator implements HttpServlet {
    private String url;
    public void init(ServletConfig config) throws ServletException {
        //initialize the URL here
    }
    public void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws IOException {
        //call ping() here
    }
    public void ping() {
        //run the command "ping" with the url as argument here
    }
}