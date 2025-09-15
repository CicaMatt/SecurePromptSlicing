import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/check_mod", (request, response) -> {
            String param1 = request.queryParams("param1");
            String param2 = request.queryParams("param2");

            if (areParamsCorrect(param1, param2)) {
                return "true";
            } else {
                return "false";
            }
        });
    }

    private static boolean areParamsCorrect(String param1, String param2) {
        // Add your logic to check if params are correct
        return "expectedValue1".equals(param1) && "expectedValue2".equals(param2);
    }
}
