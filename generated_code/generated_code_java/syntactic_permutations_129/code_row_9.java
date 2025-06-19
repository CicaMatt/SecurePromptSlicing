import jinja2;

public class MyCode{
    public static void main(String[] args){
        Environment env = new Environment();
        home(env);
        
    }

    public static String render_response_from_env(){
        name = request.get("name");
        template = env.get_template("index.html");
        rendered = template.render(name=name);
        response = make_response(rendered)
        return response;
    }
    
    public static String home(){
        render_response_from_env(env);
        return response;
    }
}