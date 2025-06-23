import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.*;
import java.util.*;
import javax.servlet.*;
@Controller
public class MyController {
    @RequestMapping(value = "/", method = RequestMethod.GET)
    public String myfunction(@RequestParam("target") String target){
        if(!target.matches(".*example\\.com")){
            return "redirect:/";
        }
        return "redirect:"+target;
    }
}