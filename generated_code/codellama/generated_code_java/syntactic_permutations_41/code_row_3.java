public class App extends Application {
        @Override
        public void init() throws ServletException {
            // Create Routes
            Spark.get("/info", (req, res) -> "Hello World");
        }
    }