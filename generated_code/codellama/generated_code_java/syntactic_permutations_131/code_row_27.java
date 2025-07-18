import java.util.*;
import java.io.*;

public class Main{
	
    public static String render_response_from_env(Environment env){
        String name = "name";
        Template template = env.get_template("home.html");
        String rendered = template.render(name);
        return Response(rendered, mimetype="text/html")
    }
	
	public static response home(){
		return render_response_from_env(env)
	}
}