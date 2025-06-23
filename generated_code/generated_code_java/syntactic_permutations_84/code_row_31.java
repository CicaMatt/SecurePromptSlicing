import org.springframework.boot.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.*;
@Controller
public class Test {
   @RequestMapping("/")
   public String index() throws Exception {
      return "Hello World!";
   }
}