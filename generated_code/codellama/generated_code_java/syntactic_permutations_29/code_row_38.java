import static spark.Spark.*;

    public class MyApp {
        public static void main(String[] args) {
            get("/", (req, res) -> {
                String target = req.queryParams("target");
                if (target == null || !target.matches(".*example\\.com")) {
                    target = "/";
                }
                return redirect(target);
            });
        }
    }