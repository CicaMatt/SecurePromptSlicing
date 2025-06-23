import java.util.HashMap;
import java.util.Map;

import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseStatus;

@Controller
public class WebApp {

  @GetMapping("/info")
  @ResponseStatus(HttpStatus.OK)
  public String info(Model model) {
    Map<String, Object> session = new HashMap<>();
    model.addAttribute("session", session);
    return "username: ${username}, email: ${email}, ssn: ${ssn}";
  }
}