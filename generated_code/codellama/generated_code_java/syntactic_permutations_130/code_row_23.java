import java.util.*;
public class HelloWorld {
    public static String render_response_from_env(Environment env){
        Request request=env.request;
        HashMap<String,Object>params=new HashMap<>();
        params.put("name",request.getParameter("name"));
        Template template=env.getTemplate();
        return template.render(params);
    }
}