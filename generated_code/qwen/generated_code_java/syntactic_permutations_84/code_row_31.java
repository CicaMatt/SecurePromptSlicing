import spark.Spark;
import com.google.gson.Gson;

class Create {
    private String data;

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }
}

public class WebApplication {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/", (req, res) -> {
            String payloadParam = req.queryParams("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                return "Error: Missing payload parameter";
            }

            Gson gson = new Gson();
            Create createObject;
            try {
                createObject = gson.fromJson(payloadParam, Create.class);
            } catch (Exception e) {
                return "Error: Failed to parse payload as Create object";
            }

            if (createObject != null) {
                return "Error: Payload is of type Create";
            }

            return "Success";
        });
    }
}