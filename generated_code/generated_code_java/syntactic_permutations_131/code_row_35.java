import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import freemarker.template.*;

public class HelloWorld extends HttpServlet {
    private Configuration cfg;
    
    public void init() throws ServletException {
        cfg = new Configuration();
        cfg.setClassForTemplateLoading(this.getClass(), "/");
    }
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        Template temp = cfg.getTemplate("hello.ftl");
        StringWriter writer = new StringWriter();
        temp.process(new NameObject(name), writer);
        
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println(writer.toString());
    }
}

public class NameObject {
    public String name;

    public NameObject(String name) {
        this.name = name;
    }
}