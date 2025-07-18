import java.io.*;
    import java.util.*;
    import com.mashape.unirest.http.Unirest;
    import com.mashape.unirest.http.exceptions.UnirestException;
    
    public class Main {
        public static void main(String[] args) throws UnirestException {
            String env = "https://api.github.com";
            String name = "Github";
            Response response = render_response_from_env(env);
            System.out.println(response.getBody());
        }
    
        public static Response render_response_from_env(String env) throws UnirestException {
            String template = "Hello, {name}!";
            Map<String, Object> model = new HashMap<>();
            model.put("name", name);
            String rendered = Template.render(template, model);
            return Response.ok(rendered).build();
        }
    }