import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

public class HelloWorldDecorator{
  @RequestMapping("/hello/{username}")
  public ModelAndView hello(@PathVariable String username) {
    return new ModelAndView("hello", "user", username);
  }
}