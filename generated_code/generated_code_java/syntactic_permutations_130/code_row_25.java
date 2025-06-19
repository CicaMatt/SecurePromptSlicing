import java.io.IOException;
import com.mashape.unirest.http.Unirest;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Main {
    @RequestMapping(value = "/", method = RequestMethod.GET)
    public String render_response_from_env(Environment env) throws IOException {
        String nameParameter = env.getRequest().getParameter("name");
        Template template = env.getTemplate("index.html");
        return template.render(Context.of("name", nameParameter));
    }
    
    @RequestMapping(value = "/home", method = RequestMethod.GET)
    public ResponseEntity<String> home() throws IOException {
        String url = "http://localhost:8080/";
        ResponseEntity<String> response = Unirest.get(url).asString();
        return render_response_from_env(env);
    }
}