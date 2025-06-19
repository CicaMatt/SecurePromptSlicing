import java.util.*;  
    class Main {
    public static String render_response_from_env(Environment env){
        Map<String,Object> request = new HashMap<String,Object>();  
        request.put("name","John");   
        Template template = env.get_template("test.html");
        String rendered_template = template.render(request);
        return rendered_template;
    }
    public static String home(Environment env){
        String response = render_response_from_env(env);
        return response;
    } 
}