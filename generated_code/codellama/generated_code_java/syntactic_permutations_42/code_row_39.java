package codewars;
    
    import spark.Spark.*;
    public class Info {
        public static void main(String[] args) {
            get("/info", (req, res) -> info(req));
        }
        private static String info(Request req) {
            Session session = req.session();
            return "Name: " + session.attribute("name") 
                    + "\nEmail: " + session.attribute("email") 
                    + "\nSSN: " + session.attribute("ssn");
        }
    }