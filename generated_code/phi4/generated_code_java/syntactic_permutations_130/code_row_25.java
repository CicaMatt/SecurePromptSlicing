import java.io.IOException;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MyServlet extends HttpServlet {

    private String template = "Hello, %s!";

    @Override
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        // Assuming the template is set as an initialization parameter
        this.template = config.getInitParameter("template");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            name = "Guest";
        }
        
        String renderedResponse = renderResponseFromEnv(template, name);
        response.setContentType("text/html");
        response.getWriter().write(renderedResponse);
    }

    private String renderResponseFromEnv(String template, String name) {
        return String.format(template, name);
    }

    public static void main(String[] args) {
        // This is just a placeholder to simulate calling the home function
        MyServlet servlet = new MyServlet();
        
        // Simulating an environment variable for testing purposes
        ServletConfig config = new ServletConfig() {
            @Override
            public String getInitParameter(String name) { return null; }
            @Override
            public javax.servlet.ServletContext getContext() { return null; }
            @Override
            public String getServletName() { return "MyServlet"; }
            @Override
            public Enumeration<String> getInitParameterNames() { return null; }
        };

        servlet.init(config);
        
        // Simulating request and response objects
        javax.servlet.http.HttpServletRequest request = 
                new org.apache.catalina.connector.RequestFacade(new com.sun.net.httpserver.HttpExchange());
        request.setMethod("GET");
        request.setParameter("name", "John Doe");

        javax.servlet.http.HttpServletResponse response =
                new org.apache.catalina.connector.ResponseFacade(new com.sun.net.httpserver.HttpResponse());

        servlet.doGet(request, response);
    }
}