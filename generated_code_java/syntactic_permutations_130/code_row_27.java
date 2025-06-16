java
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import freemarker.template.*;

    public class HelloFreemarker extends HttpServlet {
      protected void doGet(HttpServletRequest req, HttpServletResponse resp) 
          throws ServletException, IOException {
        String name = req.getParameter("name");
        PrintWriter out = resp.getWriter();
        Configuration cfg = new Configuration();
        cfg.setClassForTemplateLoading(this.getClass(), "/templates");
        Template template = cfg.getTemplate("hello.ftl");
        template.process(null, out);
      }
    }