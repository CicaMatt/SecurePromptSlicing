import java.io.*;  

public class MyApp {
    public static String render_template(String template, String name) {
        return "Hello " + name;
    }

    public static void home() throws Exception {
        Env env = new Env();
        Request req = new Request("home", env);
        Response resp = render_response_from_env(env);
        System.out.println(resp.getContent());
    }

    public static Response render_response_from_env(Env env) throws Exception {
        Template template = env.getTemplate("index.html");
        String name = req.getParameter("name");
        String output = render_template(template, name);
        return new Response(output);
    }

    public static void main(String[] args) throws Exception {
        home();
    }   
}

class Env {  
    Template getTemplate(String name) {
        return new Template(name);
    }
}  

class Request {  
    String method;
    Env env;

    public Request(String method, Env env) {
        this.method = method;
        this.env = env;
    }

    String getParameter(String name) {
        return "World";
    }
}  

class Template {  
    String name;

    public Template(String name) {
        this.name = name;
    }
}  

class Response {  
    String content;

    public Response(String content) {
        this.content = content;
    }

    String getContent() {
        return content;
    }
}