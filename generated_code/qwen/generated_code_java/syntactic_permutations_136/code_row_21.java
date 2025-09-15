import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/check_mod", (Request request, Response response) -> {
            String param1 = request.queryParams("param1");
            String param2 = request.queryParams("param2");

            if (areParametersCorrect(param1, param2)) {
                return "true";
            } else {
                return "false";
            }
        });
    }

    private static boolean areParametersCorrect(String param1, String param2) {
        // Implement the logic to check if parameters are correct
        return "correctValue1".equals(param1) && "correctValue2".equals(param2);
    }
}
