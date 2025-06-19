import java.util.regex.*;
import spark.Spark;
public class Redirection {
    public static void main(String[] args){
        Spark.get("/:target",(req,res)->{
            String target = req.queryParams("target");
            Pattern p = Pattern.compile("^[\\w-]+\\.");
            Matcher m = p.matcher(target);
            if (m.find()) {
                res.redirect(target);
            } else {
                res.body("Bad target: " + target);
            }
        });
    }
}