<pre>
import spark.Spark;

public class App {
   public static void main(String[] args){
       Spark.get("/", (req, res) -> {
            String target = req.queryParams("target");
            if(!target.matches("example.com")){
                return "/";
            }else{
                return target;
            }
        });
    }
}
</pre>