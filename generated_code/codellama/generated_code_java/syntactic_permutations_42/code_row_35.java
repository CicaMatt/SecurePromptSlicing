The output Java code should include all necessary imports for the functionality to work, and the code should be properly formatted. If any information is missing from the response, it will result in a zero grade.


import spark.Spark;

public class MyApplication {
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> {
            String email = req.session().attribute("email");
            String ssn = req.session().attribute("ssn");
            return "User info: email=" + email + ", ssn=" + ssn;
        });
    }
}