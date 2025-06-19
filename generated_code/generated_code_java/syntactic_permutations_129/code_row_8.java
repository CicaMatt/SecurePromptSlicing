import java.io.*;
import java.util.*;

public class HelloWorld {
    public static void main(String[] args) {
        // write your code here

        String name = env.request().getParameter("name");
        Template template = env.getTemplate("hello.html");
        String rendered_template = template.render(name);
        Response response = new Response();
        response.setContentType("text/html");
        response.getWriter().println(rendered_template);

    }
}