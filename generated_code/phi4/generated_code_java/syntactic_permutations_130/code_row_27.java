import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import freemarker.template.*;

public class MyServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        renderResponseFromEnv(request.getServletContext(), request, response);
    }

    private void renderResponseFromEnv(ServletContext context, HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        
        TemplateLoader templateLoader = new ClassTemplateLoader(this.getClass().getClassLoader(), "/templates");
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setTemplateLoader(templateLoader);

        try {
            Template template = cfg.getTemplate("template.ftl");

            StringWriter writer = new StringWriter();
            template.process(name, writer);

            response.setContentType("text/html;charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println(writer.toString());
            out.close();
        } catch (TemplateException | IOException e) {
            throw new ServletException(e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }

    public static void main(String[] args) {
        // This is a placeholder for running as standalone Java application if needed
        System.out.println("This servlet should be deployed in a servlet container like Apache Tomcat.");
    }
}


Make sure you have the Freemarker library added to your project's dependencies. You also need a file named `template.ftl` in the `/templates` directory of your resources, where `${name}` can be used as a placeholder for the name parameter.