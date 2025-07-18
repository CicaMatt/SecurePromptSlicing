import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.*;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
@Controller
public class MyController {
    @GetMapping("/redirect")
    public ModelAndView redirect(@RequestParam("target") String target) throws IOException {
        String regex = "^[A-Za-z0-9-]+\\.[A-Za-z0-9.]+$";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(target);
        ModelAndView mv = new ModelAndView();
        if (matcher.matches()) {
            return mv.setViewName("redirect:/" + target);
        } else {
            return mv.setViewName("redirect:/");
        }
    }
}