package com.mycompany;
import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
public class Response {
    private String name;
    public void render_response(Environment environment) {
        this.name = environment.getRequest().getParameter("name");
        Template template = environment.getTemplate();
        VelocityContext context = new VelocityContext();
        context.put("name", this.name);
        template.merge(context, environment.getResponse());
    }
}