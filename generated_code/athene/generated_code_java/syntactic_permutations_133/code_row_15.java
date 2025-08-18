import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/hello", (req, res) -> "Hello, World!");
        Spark待.init();
    }
}


Note: There seems to be a character encoding issue with the last line. It should read `Spark.init();` instead of `Spark待.init();`. Here is the corrected version:


import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/hello", (req, res) -> "Hello, World!");
        Spark.init();
    }
}