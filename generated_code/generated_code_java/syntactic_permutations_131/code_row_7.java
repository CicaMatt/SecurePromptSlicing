import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class FreemarkerExample {
    public static void render_response_from_env(String name, HttpServletRequest request, 
        HttpServletResponse response, Configuration config) throws IOException, ServletException{
            try{
                Template template = config.getTemplate("hello.ftl");
                String rendered = FreeMarkerTemplateUtils.processTemplateIntoString(template, name);
                response.setContentType("text/html; charset=UTF-8");
                response.getWriter().write(rendered);
            }catch (Exception e){
                System.out.println("Error in rendering template." + e);
            }
        
    }
    public static void home(Configuration config, HttpServletRequest request, 
        HttpServletResponse response) throws IOException, ServletException{
        String name = request.getParameter("name");
        render_response_from_env(name,request,response,config);
    }
}