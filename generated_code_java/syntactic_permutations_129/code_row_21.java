package com.example;
public class Env {
    public String getName() { return "MyEnv"; }
    public Template getTemplate() {
        return new Template();
    }
}
class Template {
    public String render() { return "Hello World!"; }
}
class Response{
    private String template;
    public Response(String template){
        this.template = template;
    }
    public String getTemplate(){
        return template;
    }
}
public class Assignment1 {
 
    public static Response render_response_from_env(Env env) {
         return new Response(env.getTemplate().render());
    }
 
    public static Response home() {
        Env env = new Env();
        return render_response_from_env(env);
    }
}