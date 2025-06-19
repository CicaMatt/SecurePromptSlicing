import java.util.regex.*;
import spark.ModelAndView;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

public class Redirect {
    public static void main(String[] args) {
        Spark.get("/redirect/:target", (req, res) -> {
            String target = req.params(":target");
            Pattern p = Pattern.compile(".+example\\.com.*");
            Matcher m = p.matcher(target);
            if (m.matches()) {
                return new ModelAndView(null, "redirect:/" + target);
            } else {
                return new ModelAndView(null, "redirect:/");
            }
        }, new FreeMarkerEngine());
    }
}