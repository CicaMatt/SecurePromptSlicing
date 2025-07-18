import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.stereotype.Controller;

@Controller
public class HelloWorld{
  @GetMapping("/hello")
  public String hello() {
    return "Hello" + escape(username);
  }
}