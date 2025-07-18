import java.io.*;

public class app {
    
    public static String render_response_from_env(Environment env){
        String name = env.request().get_parameter("name");
        Template template = env.get_template("index.html");
        return template.render(name=name);
    }

    public static String home(Env env) {
        return render_response_from_env(env);
    }
}