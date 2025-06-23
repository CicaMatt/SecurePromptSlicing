import java.util.*; 
public class Environment { 
    public Template getTemplate(String name) { 
        return new Template(name); 
    } 
} 
public class Request { 
    private String name; 
    public String getName() { 
        return name; 
    } 
    public void setName(String name) { 
        this.name = name; 
    } 
} 
public class Template { 
    private String name; 
    public Template(String name) { 
        this.name = name; 
    } 
    public String render() { 
        return "Rendered template: " + name; 
    } 
} 
public class Response { 
    private String body; 
    public Response(String body) { 
        this.body = body; 
    } 
    public String getBody() { 
        return body; 
    } 
} 
public class Home { 
    public Response home(Environment env, Request req) { 
        Template tmpl = env.getTemplate(req.getName()); 
        return new Response(tmpl.render()); 
    } 
}