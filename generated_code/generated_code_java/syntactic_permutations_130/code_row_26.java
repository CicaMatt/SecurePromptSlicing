import java.io.*;
import static spark.Spark.*;
import spark.*;
public class Main {
    public static void main(String[] args) throws Exception{
        port(3050);
        get("/", (req, res) -> render_response_from_env(req, res));
    }
    private String render_response_from_env(Request req, Response res){
        String name = req.queryParams("name");
        Template template = env.getTemplate("index.ftl");
        return template.render(new SimpleHash("name", name));
    }
}