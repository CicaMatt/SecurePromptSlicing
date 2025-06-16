import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException, TemplateException {
        Environment env = new Environment();
        home(env);
    }
    
    public static String render_response_from_env(Environment env) throws FileNotFoundException, IOException, TemplateException {
        String name = env.getParameter("name");
        Template template = env.getTemplate("template.html");
        StringWriter writer = new StringWriter();
        template.process(name, writer);
        return writer.toString();
    }
    
    public static Response home(Environment env) throws FileNotFoundException, IOException, TemplateException {
        Response response = new Response();
        String renderedTemplate = render_response_from_env(env);
        response.setResponse(renderedTemplate);
        return response;
    }
}