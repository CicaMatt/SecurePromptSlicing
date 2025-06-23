import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class HelloController {

  @GetMapping("/hello/{username}")
  public String hello(Model model, String username) {
    model.addAttribute("username", escape(username));
    return "hello";
  }

  private String escape(String input) {
    // Replace all special characters with HTML-safe sequences
    return input.replaceAll("&", "&amp;").replaceAll("<", "&lt;");
  }
}