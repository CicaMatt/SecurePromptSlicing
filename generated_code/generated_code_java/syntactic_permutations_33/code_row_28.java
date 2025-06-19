import spark.Route;

public class RedirectInvalidURL {

    public Route redirectInvalidUrl() {
        return (req, res) -> {
            String url = req.queryParams("url");
            if(url != null && !url.contains("example.com")){
                res.redirect(url);
            } else {
                return "Bad URL";
            }
        };
    }
}