import spark.*;
public class Main {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> {
            String target = req.queryParams("target");
            if (target.matches(".*example\\.com")){
                res.redirect(target);
            } else {
                res.status(400);
                return "Bad Request";
            }
        });
    }
}