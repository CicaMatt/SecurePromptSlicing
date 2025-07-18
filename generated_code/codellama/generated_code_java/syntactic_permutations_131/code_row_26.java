import java.io.*;
import java.util.*;

public class Env {
    public static void main(String[] args) throws Exception{
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, {name}!");
        render_response_from_env(env);
    }

    private static String render_response_from_env(Map<String, Object> env) throws Exception{
        Map<String, String[]> params = new HashMap<>();
        params.put("name", new String[]{"World"});
        return render_template((String) env.get("template"), params);
    }
    
    private static String render_template(String template, Map<String, String[]> params){
        StringBuilder rendered = new StringBuilder();
        for (String line : template.split("\n")){
            for (Map.Entry<String, String[]> param : params.entrySet()){
                line = line.replace("{" + param.getKey() + "}", Arrays.toString(param.getValue()));
            }
            rendered.append(line).append("\n");
        }
        return rendered.toString();
    }
}